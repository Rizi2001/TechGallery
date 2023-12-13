from rest_framework.response import Response
from rest_framework.views import APIView
from django.core.files.storage import FileSystemStorage
from django.conf import settings
# import whisper
from faster_whisper import WhisperModel
import os, glob, re, subprocess
import numpy as np
import torch, traceback


model_size = "large-v2"

model = WhisperModel(model_size, device="cuda")


class SoapNote(APIView):

    def post(self, request):
        try:
            if not request.FILES.get('file',None):
                return Response({"status": "Failure", "message : ": "File is required"}, status=400)
            
            file = request.FILES['file']

            fs = FileSystemStorage(location=str(settings.BASE_DIR) + "/uploaded_files")
            filename = fs.save(file.name, file)
            location=str(settings.BASE_DIR)+"/uploaded_files/"+filename

            # result = pro_whisper_model.transcribe(location, fp16=False, language='english')
            segments, info = model.transcribe(location, beam_size=1)


            result=''

            for segment in segments:
                # print("[%.2fs -> %.2fs] %s" % (segment.start, segment.end, segment.text))
                # print(segment.text)
                result += segment.text

            result_text = result

            return Response({"result": result_text}, status=200)

        except Exception as e:
            traceback.print_exc()
            return Response({"status": "Failure", "message : ": str(e)}, status=400)






