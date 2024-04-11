import serial
import time

# Define the serial port and baud rate
# Change these values according to your setup
serial_port = '/dev/ttyUSB0'  # Change this to the appropriate port
baud_rate = 2400

No_of_bits=11 #adjust the no. of bits according to (parity + stop bit  + start bit +wordlength) settings


# Create a serial object
ser = serial.Serial(serial_port, baud_rate)
time.sleep(2)  # Wait for the serial connection to initialize

try:
    
    #__________________________PC_To_MCU_____________________________________
    command = "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one. \n In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs,\" Rajan said in the note.\" Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently.\r"

    temp1=time.time()
    for i in range(len(command)):
        ser.write(command[i].encode())
        temp2=time.time()
        print(((No_of_bits)/(temp2-temp1)))
        temp1=temp2

    #__________________________MCU_To_PC______________________________________
    p=2
    data_raw=""
    
    temp1=time.time()
    recieve=""
    while True:
        
        data_raw = ser.read().decode()
        temp2=time.time()    
        
        print(((No_of_bits)/(temp2-temp1)))
        if data_raw =="\n":
            p-=1
        if p==0:
            p-=1
            print(recieve)
        recieve+=data_raw
        temp1=temp2
except:
    print("\nExiting program.")

finally:
    # Close the serial connection
    ser.close()
