import chromadb
import bs4
import requests
import re
from langchain.text_splitter import SentenceTransformersTokenTextSplitter

URL = "https://svthw.org/20-home-remedies-everyone-should-know/"
CHROMA_COLLECTION_NAME = "home-remedies"
CHROMADB_DIR = "health_db/"


def fetch_content(url: str) -> str:
    # Set headers to mimic a browser request
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'
    }

    # Fetch the URL content
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        return response.text
    else:
        raise Exception(f"Failed to fetch the webpage. Status Code: {response.status_code}")


if __name__ == '__main__':
    # Create ChromaDB collection
    chroma_client = chromadb.PersistentClient(path=CHROMADB_DIR)
    collection = chroma_client.get_or_create_collection(name=CHROMA_COLLECTION_NAME)
    text_splitter = SentenceTransformersTokenTextSplitter()

    # Fetch and parse content from the URL
    html_content = fetch_content(URL)
    soup = bs4.BeautifulSoup(html_content, 'html.parser')

    last_header = ""
    paragraphs = soup.find_all("p")

    # Iterate through paragraphs and add relevant ones to ChromaDB
    for n, paragraph in enumerate(paragraphs):
        text = paragraph.text.strip().lower()

        # Add filtering logic to select only relevant paragraphs containing remedies or treatments
        # if "remedy" in text or "treatment" in text or "natural cure" in text or "cure" in text:
        paragraph_id = f"home_remedies_{n}"

        # Find the previous header
        header = paragraph.find_all(re.compile("^h[1-5]$"))
        if header:
            header = header[0].text.strip()
            last_header = header
        else:
            header = last_header

        # Split the text into chunks and insert into ChromaDB
        ids = []
        documents = []
        metadatas = []
        chunks = text_splitter.create_documents([text])  # Takes an array of documents
        for chunk_no, chunk in enumerate(chunks):
            ids.append(f"{paragraph_id}#{chunk_no}")
            documents.append(chunk.page_content)
            metadatas.append({"title": header, "source": URL})

        if ids:
            collection.upsert(ids=ids, documents=documents, metadatas=metadatas)

        print(f"{int(0.5 + 100.0 * n / len(paragraphs))}% ({collection.count()})", end=" ", flush=True)
        if n % 10 == 0:
            print()
