import os
import ast
import spacy
import numpy as np
import pandas as pd
from csv import DictWriter
from sentence_transformers import util
from vertexai.language_models import TextEmbeddingModel
from flask import Flask, render_template, request

app = Flask(__name__)

os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "aiml-365220-7d5d084cd436.json"

embedding_df = pd.read_csv("Question_Variations_Embeddings.csv")

embedding_df['Embedding'] = embedding_df['Embedding'].apply(ast.literal_eval)

question_embeddings = embedding_df['Embedding']

model = TextEmbeddingModel.from_pretrained("textembedding-gecko@001")

nlp = spacy.load("en_core_web_sm")

def preprocess_text(text):
    doc = nlp(text)
    return " ".join([token.lemma_ for token in doc if not token.is_punct])

def save_response_to_csv(question, sim_score, answer):
    PATH = os.getcwd() + '/static/input_questions.csv'
    user_input = request.form['user_input']
    dict={'Question':user_input, 'Similarity_Score': sim_score, 'Answer': answer}
    with open(PATH, 'a') as f_object:
        dictwriter_object = DictWriter(f_object, fieldnames=['Question', 'Similarity_Score', 'Answer'])
        dictwriter_object.writerow(dict)
        f_object.close()
    return 


def get_most_similar_question(user_question, question_embeddings_df):
    user_question = preprocess_text(user_question)
    
    user_question_embedding = model.get_embeddings([user_question])
    
    user_question_embedding = [embedding.values for embedding in user_question_embedding]

    sim_score = [util.pytorch_cos_sim(user_question_embedding, i).item() for i in question_embeddings]

    threshhold = 0.83
    
    max_sim_score = max(sim_score)

    print("Maximum similarity Score: ", max_sim_score)

    try:
        save_response_to_csv(user_question, max_sim_score, embedding_df['Answer'][sim_score.index(max_sim_score)])
    except Exception as e:
        print("Exception:", e)
        pass

    if max_sim_score >= threshhold:
        sim_arg = sim_score.index(max_sim_score)

        return embedding_df['Answer'][sim_arg]
    else:
        return "Sorry, I didn't understand your question, please contact sales"


@app.route('/', methods=['GET', 'POST'])
def chat():
    response = ""
    
    if request.method == 'POST':
        user_input = request.form['user_input']
        
        if not user_input.strip():
            response = "Invalid input. Please enter a valid question."
        else:
            try:
                response = get_most_similar_question(user_input, embedding_df)
            except Exception as e:
                print("Exception:", e)
                response = "An error occurred while processing your request. Please try again."
    #if request.method == 'POST':
     #   user_input = request.form['user_input']
        
  
      #  response = get_most_similar_question(user_input, embedding_df)
 
    return render_template('chat.html', response=response)

if __name__ == '__main__':
    app.run(debug=True)
