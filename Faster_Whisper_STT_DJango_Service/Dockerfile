FROM python:3.8

WORKDIR /usr/src/app
COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt
RUN apt-get update && apt-get install ffmpeg libsm6 libxext6  -y
COPY . .

CMD ["python3", "/usr/src/app/manage.py", "runserver", "0.0.0.0:8000"]
