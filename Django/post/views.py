from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from home.models import Sensor


# Create your views here.
def post(request):
    updated_sensor_id = int(request.POST.get('sensor_id'))
    value = int(request.POST.get('value'))
    selected_sensor = Sensor.objects.get(sensor_id=updated_sensor_id)
    selected_sensor.value = value
    selected_sensor.save()
    return HttpResponse("200")

def api(request):
    selected_sensor = Sensor.objects.get(sensor_id=request.GET.get('sensor_id'))
    selected_sensor_minimum_value = selected_sensor.minimum_value
    selected_sensor_alert_value = selected_sensor.alert_value
    selected_sensor_data_to_json = {
        "minimum_value": selected_sensor_minimum_value,
        "alert_value": selected_sensor_alert_value,
    }
    return JsonResponse(selected_sensor_data_to_json)
