from django.shortcuts import render
from .models import Sensor

def index(request):
    sensors = Sensor.objects.all()
    data = {'sensors': sensors}
    return render(request, 'home/index.html', data)

def sensor(request, sensor_id):
    return render(request, 'home/sensor.html')
