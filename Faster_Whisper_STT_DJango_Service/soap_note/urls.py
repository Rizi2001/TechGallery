from django.urls import path
from . import views

app_name = 'soap_note'

urlpatterns = [
    path("generate_soap/", views.SoapNote.as_view(), name="generate_soap"),
]
