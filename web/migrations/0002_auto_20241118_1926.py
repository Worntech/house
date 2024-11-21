# Generated by Django 3.2.25 on 2024-11-18 16:26

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('web', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='mypayment',
            name='Month',
            field=models.IntegerField(choices=[(3, '3 Months'), (6, '6 Months')]),
        ),
        migrations.AlterField(
            model_name='mypayment',
            name='end_date',
            field=models.DateTimeField(blank=True, null=True),
        ),
    ]