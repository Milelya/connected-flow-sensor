# Generated by Django 3.0 on 2020-12-18 04:49

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Sensor',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('sensor_name', models.CharField(max_length=50)),
                ('sensor_id', models.IntegerField()),
                ('value', models.IntegerField()),
                ('minimum_value', models.IntegerField()),
                ('alert_value', models.IntegerField()),
            ],
        ),
    ]
