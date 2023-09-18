from flask import Flask, render_template, request
import requests
import os
from vertexai.preview.language_models import ChatModel, InputOutputTextPair

os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "" #Replace with you GCP Service account credentials JSON file

model = ChatModel.from_pretrained("chat-bison@001")
#model = ChatModel.from_pretrained("text-bison@001") 

def generate_variations_vertex(prompt):

    full_prompt = f"Act as a doctor so when a patient tells you its problems, you identify the cause of the problem and suggest some home remedies. The patient query is as follows: \"{prompt}"
    chat = model.start_chat()

    response = chat.send_message(prompt,max_output_tokens=256,temperature=0.3)

    return (response.text)

#prompt = "Write me two paragraphs on sexual orientation"


# prompt="I have a stomach ache along with a on and off headache since yesterday. I'm drinking a lot of juices but they don't seem to help"

#response=generate_variations_vertex(prompt)
#print((response))

# app = Flask(__name__)

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/get_response', methods=['POST'])
def get_response():
	user_input = request.form['user_input']

	response = generate_variations_vertex(user_input)

	return response

if __name__ == '__main__':
	app.run(debug=True)
