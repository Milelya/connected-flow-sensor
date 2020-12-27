from django.db import models

# Create your models here.
class Sensor(models.Model):
    sensor_name = models.CharField(max_length=50)
    sensor_id = models.IntegerField()
    value = models.IntegerField()
    minimum_value = models.IntegerField()
    alert_value = models.IntegerField()

    def __str__(self):
        return self.sensor_name