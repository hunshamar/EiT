
import firebase_admin
from firebase_admin import credentials, firestore
import time
import datetime

import serial

cred = credentials.Certificate("ServiceAccountKey.json")

default_app = firebase_admin.initialize_app(cred)

db = firestore.client()



doc_ref_ph = db.collection(u'sensors').document(u'DrcB0MYwfE4c19RiQ5L5')
doc_ref_Temp = db.collection(u'sensors').document(u'MygNSJp4Kz6KCVReFjsV')
doc_ref_CO2 = db.collection(u'sensors').document(u'UA4UDs3e5JfqJavKGAzF')
doc_ref_Jord = db.collection(u'sensors').document(u'yBCzlLYBMuW3DkUlEc7N')
doc_ref_VOC = db.collection(u'sensors').document(u'SwfptPItPGllTnUHCepY')






def addData(t, value, sensorRef):


    doc = sensorRef.get()

    dataDict = doc.to_dict()


    name = dataDict["name"]

    valueArray = dataDict["value"]
    valueArray.append(value)


    timeArray = dataDict["time"]
    timeArray.append(t)




    sensorRef.set({
        u'name' : name,
        u'value' : valueArray,
        u'time' : timeArray
    })


def clearData(sensorRef):



    doc = sensorRef.get()
    dataDict = doc.to_dict()
    name = dataDict["name"]

    sensorRef.set({
        u'name' : name,
        u'value' : [],
        u'time' : []
    })


clearData(doc_ref_Jord)
clearData(doc_ref_CO2)
clearData(doc_ref_VOC)



## Endre til hva raspberry bruker ##
ser = serial.Serial('/dev/ttyACM3', 9600)  


## Nå er format:   begin:sensor|data:sensor|data:sensor|data:end ##
## eksempel    :   begin|co2:400|VOC:4|end                       ##

a = 5
t = 100

while True:  

    data = str(ser.readline())
    


    if data:
        print(data)
 
        sensorData = data.split("|")
        if sensorData[0] == "b'begin":             ##Sjekker at første del er 'begin'


            currentTime = datetime.datetime.now()


            print("Sensor read: ", end="")
            for i in range(1, len(sensorData)-1):  ##leser ut for hver sensor på format 'sensor-data'


                

                read = sensorData[i].split(":")    ##splitter i navn og data 
                sensorName = read[0]
                sensorValue = read[1]

                print(sensorName+":",sensorValue,"   ",end="")
                if sensorName == "HM":
                    addData(currentTime, sensorValue, doc_ref_Jord)
                if sensorName == "CO2":
                    addData(currentTime, sensorValue, doc_ref_CO2)
                if sensorName == "VOC":
                    addData(currentTime, sensorValue, doc_ref_VOC)


                addData(currentTime, "error", doc_ref_ph)
                addData(currentTime, "error", doc_ref_Temp)

                ser.flushInput() ## Empty buffer of recieved data from line. Will wait until next serial data 

                    