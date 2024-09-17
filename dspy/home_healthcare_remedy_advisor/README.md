## Example of building an healthcare assistant with DSPy

It covers modules of DSPy starting from ZeroShot questioning to RAG (Retreival Augmented Generation), CoT (Chain of Thought) and lastly, fine-tuning the llm on trainingdata.json dataset then Q/A on the trained model.


### How to run
```
Install the requirements:
```commandline
pip install -r requirements.txt
```
Create a file named api_keys.env and add one/both of the following lines:
```commandline
GOOGLE_API_KEY=AI...
```
Index the healthcare content into Chroma DB:
```commandline
python index_healthcare_db.py
```
Main command:
```commandline
python health_advisor.py
```
