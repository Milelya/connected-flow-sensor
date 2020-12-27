from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('sensor/<int:sensor_id>/', views.sensor, name = 'sensor'),
]