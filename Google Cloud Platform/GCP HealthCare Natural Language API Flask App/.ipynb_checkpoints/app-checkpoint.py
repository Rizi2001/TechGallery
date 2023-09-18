from flask import Flask, render_template, request
import os
import subprocess
import re

os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = ''#Path to your Google Cloud's Service Account Credentials JSON File

app = Flask(__name__)

#Parsing the output for better human understanding
def parse_result(result):   
    type_nd_cnt = []
    type1 = result.split('"entities":')[0].split('type')[1:]
    
    for i in type1:
        act_type = i.split('beginOffset')[0].split('text')[0].replace("\"","").replace(",",'').replace(":",'').strip()
        content = i.split('beginOffset')[0].split('content')[1].replace("\"","").replace(",",'').replace(":",'').strip()
        type_nd_cnt.append({'act_type':act_type, 'content':content})
        
    # type_nd_cnt
    
    
    a = ' '.join(result.split('"entities":')[1:]).split('relationships')[0].replace('\n','').replace('{','').replace(']','').replace('[','').replace('}','').strip()
        
    a = a.split('entityId')

    main_list= []
    vc = ' '.join(a).split("preferredTerm")[1:]
    for i in vc:
        print("\n\n\n")
        preferredTerm = ''.join(re.sub(r'[^\w\s]', '', ''.join(i).split("vocabularyCodes")[0]).strip())
        
        vocabularyCodes = ''.join(i).split("vocabularyCodes")[1].split(',')
        vocabularyCodes_list = []
        
        for j in vocabularyCodes:
            vocabularyCodes_list.append(re.sub(r'[^\w\s]', '', ''.join(j)).strip())
        my_dict1 = {'preferredTerm':preferredTerm, 'vocabularyCodes':vocabularyCodes_list}
        main_list.append(my_dict1)
        
        print("Main List: ", main_list)
    return main_list, type_nd_cnt


#Healthcare NLP api call with CURL
def analyze_entities(document_content):
    CurlUrl = """curl -X POST \
        -H "Authorization: Bearer "$(gcloud auth application-default print-access-token) \
        -H "Content-Type:application/json" \
        --data '{
          "nlpService":"projects/{PROJECT-ID}/locations/us-central1/services/nlp",
          "documentContent": "%s"
        }' \
        "https://healthcare.googleapis.com/v1/projects/{PROJECT ID}/locations/us-central1/services/nlp:analyzeEntities"
     """ % document_content

    status, output = subprocess.getstatusoutput(CurlUrl)
        
    return output


@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        doc_con = request.form['doc_con']
        result = analyze_entities(doc_con)
        parsed_result, type_count = parse_result(result)
        print(parse_result)
        print("doc_con:", doc_con)
        print("result:", result)

        print("parsed_result:", parsed_result)
        
        print("Type and Content:", type_count)

        return render_template('index.html', doc_con=doc_con, main_list=parsed_result, type_con = type_count)
    return render_template('index.html', doc_con='', parsed_result=[], type_con = [])


if __name__ == "__main__":
    app.run(debug=True)
  
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    