


import serial



## Endre til hva raspberry bruker ##
ser = serial.Serial('/dev/ttyACM0', 9600)  


## Nå er format:   begin:sensor|data:sensor|data:sensor|data:end ##
## eksempel    :   begin:co2|400:VOC|4:end                       ##

while True:  
    data = str(ser.readline())
    # print(data)
    if data:
        #print(data)
        sensorData = data.split(":")
        if sensorData[0] == "b'begin":             ##Sjekker at første del er 'begin'

            print("Sensor read: ")
            for i in range(1, len(sensorData)-1):  ##leser ut for hver sensor på format 'sensor-data'

                read = sensorData[i].split("|")    ##splitter i navn og data 
                # print(read)
                sensorName = read[0]
                sensorValue = (read[1])

                print(sensorName+":",sensorValue,"   ",end="")

            print("")
