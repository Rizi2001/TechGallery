import dspy
from dspy import teleprompt
from dspy.retrieve.chromadb_rm import ChromadbRM
from index_healthcare_db import CHROMADB_DIR, CHROMA_COLLECTION_NAME
import json
import requests
from bs4 import BeautifulSoup

class ZeroShot(dspy.Module):
    """
    Provide answer to health question
    """
    def __init__(self):
        super().__init__()
        self.prog = dspy.Predict("question -> answer")

    def forward(self, question):
        return self.prog(question="In the health domain, " + question)


class Definitions(dspy.Module):
    """
    Retrieve the definition from the Domestic Medicine Wikipedia page
    """
    def __init__(self):
        super().__init__()
        self.url = 'https://svthw.org/20-home-remedies-everyone-should-know/'

    def forward(self, term):
        try:
            headers = {
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'
            }
            response = requests.get(self.url, headers=headers)

            # response = requests.get(self.url)
            response.raise_for_status()  # Ensure the request is successful
            soup = BeautifulSoup(response.text, 'html.parser')

            # Search in paragraphs and headings
            paragraphs = soup.find_all(['p', 'h2', 'h3', 'li'])

            # Iterate through content to find the term
            for paragraph in paragraphs:
                if term.lower() in paragraph.text.lower():
                    return paragraph.text.strip()

            return f"No information found for {term}"

        except requests.exceptions.RequestException as e:
            return f"Error retrieving information: {str(e)}"


class FindTerms(dspy.Module):
    """
    Extract health terms from a question
    """
    def __init__(self):
        super().__init__()
        self.entity_extractor = dspy.Predict("question -> terms")

    def forward(self, question):
        max_num_terms = max(1, len(question.split()) // 4)
        prompt = f"Identify up to {max_num_terms} terms in the following question that are related to health or home remedies."
        prediction = self.entity_extractor(
            question=f"{prompt}\n{question}"
        )
        answer = prediction.terms
        if "Terms: " in answer:
            start = answer.rindex("Terms: ") + len("Terms: ")
            answer = answer[start:]
        return [a.strip() for a in answer.split(',')]


def RemedySystem():
    """
    Retrieves remedies or health-related advice from Wikipedia's Domestic Medicine page.
    """
    from chromadb.utils import embedding_functions
    default_ef = embedding_functions.DefaultEmbeddingFunction()
    return ChromadbRM(CHROMA_COLLECTION_NAME, CHROMADB_DIR, default_ef, k=3)


class AdvisorSignature(dspy.Signature):
    definitions = dspy.InputField(format=str)  # function to call on input to make it a string
    bidding_system = dspy.InputField(format=str) # function to call on input to make it a string
    question = dspy.InputField()
    answer = dspy.OutputField()
    
    
class HealthAdvisor(dspy.Module):
    """
    Functions as the orchestrator for health-related questions.
    """
    def __init__(self):
        super().__init__()
        self.find_terms = FindTerms()
        self.definitions = Definitions()
        self.prog = dspy.ChainOfThought(AdvisorSignature, n=3)

    def forward(self, question):
        terms = self.find_terms(question)
        definitions = [self.definitions(term) for term in terms]
        remedy_suggestions = RemedySystem()(question)  # Suggest remedies
        prediction = self.prog(definitions=definitions,
                               bidding_system=remedy_suggestions,
                               question="In the health domain, " + question,
                               max_tokens=-1024)
        return prediction.answer
    

def shorten_list(response):
    if type(response) == list:
        return [ f"{r['long_text'][:25]} ... {len(r['long_text'])}" for r in response]
    else:
        return response

if __name__ == '__main__':
    import dspy_init
    dspy_init.init_gemini_pro(temperature=0.0)
    
    def run(name: str, module: dspy.Module, queries: [str], shorten: bool = False):
        print(f"**{name}**")
        for query in queries:
            response = module(query)
            if shorten:
                response = shorten_list(response)
            print(response)
        print()

    # Health-related questions
    health_questions = [
        "What is a remedy for a sore throat?",
        "How to relieve a headache naturally?",
        "What can I do for acidity?"
    ]


    ### Running all modules of DSPy 

    ## Zeroshot prompting
    run("Zeroshot", ZeroShot(), health_questions)
    


    ## RAG (Retrieval Augmented Generation using chrome db and a webpage as the data source)
    run("remedy_system", RemedySystem(), health_questions, shorten=True)



    ## CoT (Chain of Thought reasoning)
    run("health_advisor", HealthAdvisor(), health_questions)



    ## Fine-tuning on example trainingdata.json
      
    traindata = json.load(open("trainingdata.json", "r"))['examples']
    trainset = [dspy.Example(question=e['question'], answer=e['answer']) for e in traindata]
    
    # Train the model with few shot examples of labelled data
    teleprompter = teleprompt.LabeledFewShot()
    optimized_advisor = teleprompter.compile(student=HealthAdvisor(), trainset=trainset)
    
    run("optimized", optimized_advisor, health_questions)

    # remedy_suggestions = RemedySystem()(health_questions)
    # print(remedy_suggestions)

    # definitions_module = Definitions()
    # response = definitions_module("acidity")
    # print(response)

    
    # run("find_terms", FindTerms(), health_questions)

