import mysql.connector
import time
from threading import Timer

while 1:
    file = open('temperature.txt','r')
    file1= open('humidity.txt','r')
    t=file.readlines(1)
    h=file1.readlines(1)
    temperature = float(t[0])
    humidity=float(h[0]) 
    mydb = mysql.connector.connect(
    host="localhost",
    user="bojan",
    password="pijanista",
    database="Temperature_Humidity"
    )
    mycursor = mydb.cursor()
    sql = "INSERT INTO Temperature_Humidity (Temperature, Humidity) VALUES (%s, %s)"
    val = (temperature, humidity)
    mycursor.execute(sql, val)
    mydb.commit()
    print(mycursor.rowcount, "record inserted.")
    time.sleep(5)
    file.close()
    file1.close()