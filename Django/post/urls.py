from django.urls import path
from . import views

urlpatterns = [
    path('', views.post, name='post'),
    path('api', views.api, name='api')
]