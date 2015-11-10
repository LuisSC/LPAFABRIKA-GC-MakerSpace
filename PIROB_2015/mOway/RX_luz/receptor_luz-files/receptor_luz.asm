;***************************************************************************
;*                              mowayWorld                                 *
;***************************************************************************
;*Description:                                                             *
;*Automatically generated code                                             *
;***************************************************************************
;***************************************************************************
	list p=18F86j50
   ;*	Include mOways microcontroller
   #include "inc\P18F86j50.INC"

;****************************************
;*   Variables                          *
;****************************************
direccionTX    EQU    0x7E 
sensorluz      EQU    0x7D 

;*	Reset Vector
  org		0x1000
  goto	INIT
;*	Program memory	*
  org		0x102A
;************************
;***************************[MOWAY LIBRARIES]*********************************************
  #include "inc\lib_sen_moway_GUI.inc"
  #include "inc\lib_rf2gh4_GUI.inc"
  #include "inc\lib_mot_moway_GUI.inc"
  #include "inc\lib_cam_moway_GUI.inc"
;*************************************

INIT:

;#####################################
  ;*************************[MOWAY CONFIGURATION]***********************
  ;Sensor configuration
  call    SEN_CONFIG
  ;Motor configuration
  call    MOT_CONFIG

;****************************************
;*   Variables initialization           *
;****************************************
  movlw   .0
  movwf    direccionTX
  movlw   .0
  movwf    sensorluz

;********************Module Assign Brightness***************************

;***********************************************************************
  call    SEN_LIGHT
  movf    SEN_LIGHT_P,W
  movwf   sensorluz

;***********************************************************************
;************Module RfActivation****************************************

;***********************************************************************

;Configuration of SPI
  call	    RF_CONFIG_SPI

;Configuration of RF module (channel and dir)
  movlw	    .1		;Dir
  movwf	    RF_DIR			
  movlw	    .0		;Channel
  movwf	    RF_CHN			
  call	    RF_CONFIG
	btfss	RF_STATUS,CONFIGOK
  goto    loopEnd

;Activate the module	
  call	    RF_ON
	btfss	RF_STATUS,ONOK
  goto    loopEnd

label0:
;************Module RfReceive********************************************

;***********************************************************************

  call		RF_RECEIVE	
  btfss		RF_STATUS,RCVOK
  goto    label0
  movf     RF_DIR_IN,W
  movwf    direccionTX
  movf     RF_DATA_IN_0,W
  movwf    sensorluz

;***********************************************************************

;************Module Comparative*******************************************

;************************************************************************

  movf   sensorluz,W
  addlw   .226
  btfsc   STATUS,C
  goto    label1

;***********************************************************************
;************Module Leds************************************************

;***********************************************************************

  call    LED_FRONT_ON
  call    LED_TOP_GREEN_ON
  call    LED_TOP_RED_OFF

;***********************************************************************


  goto    label0


label1:
;************Module Leds************************************************

;***********************************************************************

  call    LED_FRONT_OFF
  call    LED_TOP_GREEN_OFF
  call    LED_TOP_RED_ON

;***********************************************************************


  goto    label0

loopEnd:
  goto    loopEnd

END
