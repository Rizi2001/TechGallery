from flask import Flask, render_template, request
from google.cloud import discoveryengine
from typing import List
import requests
import os

os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = ''#Path to your Google Cloud's Service Account Credentials JSON File


project_id = "{PROJECT ID}"
location = "global"                   
search_engine_id = '{ENTERPRISE SEARCH APP ID}'
serving_config_id = "default_search:search"  
search_query = "YOUR_SEARCH_QUERY"


def search_sample(
    project_id: str,
    location: str,
    search_engine_id: str,
    serving_config_id: str,
    search_query: str,
) -> List[discoveryengine.SearchResponse.SearchResult]:
    # Create a client
    client = discoveryengine.SearchServiceClient()

    # The full resource name of the search engine serving config
    # e.g. projects/{project_id}/locations/{location}
    serving_config = client.serving_config_path(
        project=project_id,
        location=location,
        data_store=search_engine_id,
        serving_config=serving_config_id,
    )

    request = discoveryengine.SearchRequest(
        serving_config=serving_config, query=search_query, page_size=10
    )
    response = client.search(request)
    for result in response.results:
        print(result)

    return response.results

import re

def parse_result(result):   
    find_str = 'key: "extractive_answers"\n      value {\n        list_value {\n          values {\n            struct_value {\n              fields {\n                key: "content"\n                value {\n                  string_value:'
    ans_index = str(result).find(find_str)
    ans_index
    
    final = ((str(result)[ans_index+len(find_str):]).strip())
    
    return re.sub(r'\s+', ' ', re.sub(r'[^\w\s,.!?]', '', final).replace('\n', ''))


os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = ''#Path to your Google Cloud's Service Account Credentials JSON File

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get_response', methods=['POST'])
def get_response():
    user_input = request.form['user_input']

    if not user_input.strip():
        return "Please enter a valid query" 

    response = parse_result(search_sample(project_id, location, search_engine_id, serving_config_id, user_input)) 

    if response is None:
        return "Error querying data, please try again" 

    return response

if __name__ == '__main__':
    app.run(debug=True)
