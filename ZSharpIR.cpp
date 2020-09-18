/*
	ZSharpIR

	Arduino library for retrieving distance (in mm) from the analog GP2Y0A21Y and GP2Y0A02YK,...

    Original comment from Dr. Marcal Casas-Cartagena :
	inspired from :
	- https://github.com/qub1750ul/Arduino_SharpIR.git
    - https://github.com/jeroendoggen/Arduino-GP2Y0A21YK-library.git
    - https://github.com/guillaume-rico/SharpIR.git
    - https://github.com/nikv96/MDP-Arduino.git
    - https://github.com/jeroendoggen/Arduino-GP2Y0A21YK-library.git

  

*/


#include "Arduino.h"
#include "Math.h"
#include "ZSharpIR.h"

// Initialisation function
//  + irPin : is obviously the pin where the IR sensor is attached
//  + sensorModel is a int to differentiate the two sensor models this library currently supports:
//     1080 is the int for the GP2Y0A21Y and 
//     20150 is the int for GP2Y0A02YK and 
//     100500 is the long for GP2Y0A710K0F
//    The numbers reflect the distance range they are designed for (in cm)
ZSharpIR::ZSharpIR(int irPin, const uint32_t  sensorModel) {
  
    _irPin=irPin;
    _model=sensorModel;
    
    // Define pin as Input
    pinMode (_irPin, INPUT);
    _Adcres=10;
	_refVoltage=5000;
}

// Sort an array
void ZSharpIR::sort(int a[], int size) {
    for(int i=0; i<(size-1); i++) {
        bool flag = true;
        for(int o=0; o<(size-(i+1)); o++) {
            if(a[o] > a[o+1]) {
                int t = a[o];
                a[o] = a[o+1];
                a[o+1] = t;
                flag = false;
            }
        }
        if (flag) break;
    }
}
double ZSharpIR::voltage(){
    int raw = analogRead(_irPin);
    int voltFromRaw= map(raw ,0,1023,0,5000);
    float v = voltFromRaw/1000.0;
    return v;
}
// Read distance and compute it
double ZSharpIR::distance() {

    int ir_val[NB_SAMPLE];
    double distanceMM;
    double current;

    for (int i=0; i<NB_SAMPLE; i++){
        // Read analog value
        ir_val[i] = analogRead(_irPin);
    }
    
    // Sort it 
    sort(ir_val,NB_SAMPLE);

    if (_model==999){
        distanceMM=(int)(138773.464825 * pow(ir_val[0],-1.0233470));
   }

    else if (_model==1080)//GP2Y0A21YK0F
		{
        
        // Different expressions required as the Photon has 12 bit ADCs vs 10 bit for Arduinos
          distanceMM =( 277.28 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -1.2045));


    }   
    else if (_model==20150)//GP2Y0A02YK0F
	{

        // Previous formula used by  Dr. Marcal Casas-Cartagena
        // puntualDistance=61.573*pow(voltFromRaw/1000, -1.1068);
        
        // Different expressions required as the Photon has 12 bit ADCs vs 10 bit for Arduinos
          distanceMM =( 603.74 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -1.16));


    } 
    else if (_model==1)//sensor 1
    {

        //distanceMM = (4414.1 * pow(ir_val[NB_SAMPLE/2],-0.986));
        distanceMM = (15944 * pow(ir_val[NB_SAMPLE/2],-1.209));
        /*
        current =(2125.4 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -0.802))/10;
        if(current <= 230){
            distanceMM = current;
        }
        else{
            distanceMM =(277.28 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -1.2045));
        }
        */
    }
    else if (_model==2)//sensor 2
    {
        //distanceMM = (19028 * pow(ir_val[NB_SAMPLE/2],-1.204));
        distanceMM = (55428* pow(ir_val[NB_SAMPLE/2],-1.376));
        /*
        //distanceMM =(int)(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage));
        current =(2476 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -0.734))/10;
        if(current <= 230){
            distanceMM = current;
        }
        else{
            distanceMM =(277.28 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -1.2045));
        } */
    }
    else if (_model==3)//sensor 3
    {
        distanceMM = (125859 * pow(ir_val[NB_SAMPLE/2],-1.539)); //85279  -1.471
        //distanceMM = (10460 * pow(ir_val[NB_SAMPLE/2],-1.143));
        /*
        current =(2162.5 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -0.806))/10;
        if(current <= 230){
            distanceMM = current;
        }
        else{
            distanceMM =(277.28 * pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0, -1.2045));
        } */
    }
    else if (_model==4)//sensor 4
    {
        distanceMM = (10229 * pow(ir_val[NB_SAMPLE/2],-1.142));
        //distanceMM = (2162.4* pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0,-0.878))/100; //2320.9 ^-0.895
    }
        else if (_model==5)//sensor 5
    {

        distanceMM = (9202.9 * pow(ir_val[NB_SAMPLE/2],-1.117));
        //distanceMM =(2214.5* pow(map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage)/1000.0,-0.894))/100;

    }
    else if (_model==6){
        current = -0.1056 * ir_val[NB_SAMPLE/2] + 71.065;
        if (current <=35)
        {
            distanceMM = current;
        }
        else{
            current = (26771 * pow(ir_val[NB_SAMPLE/2],-1.14)) ;
            if(current <=55){
                distanceMM = current;
            }
            else{
                distanceMM = -0.2803 * ir_val[NB_SAMPLE/2] + 119.22;
            }
        }
         /*
        if(current <= 50){
            distanceMM = current;
        }
        else
        {
            distanceMM = (17252 * pow(ir_val[NB_SAMPLE/2],-1.062)); //17252 ^-1.062
        }*/
        
        //distanceMM = (39131 * pow(ir_val[NB_SAMPLE/2],-1.21)); // accurate 60~80
        //distanceMM = (17551 * pow(ir_val[NB_SAMPLE/2],-1.071));
        //distanceMM = ((16568.54544 /(ir_val[0] + 25.35740332)) - 11); //((16724.73031 /(ir_val[0] + 25.15479286)) - 11);
    }
    else if (_model==7){
        distanceMM = map(ir_val[NB_SAMPLE / 2], 0, (1<<_Adcres)-1, 0, _refVoltage);
    }

    return distanceMM;
}




/// <summary>
/// setARefVoltage:set the ADC reference voltage: (default value: 5000mV, set to 3300mV, typically 3.3 on Arduino boards)
/// </summary>
void ZSharpIR::setARefVoltage(int refV)
{

	_refVoltage=refV;
}
/// <summary>
/// SetAnalogReadResolution:set the ADC resolution : (default value: 10, set to 12, typically 10 on Arduino boards)
/// </summary>
void ZSharpIR::SetAnalogReadResolution(int res)
{

	_Adcres=res;
	//analogReadResolution( res);
}