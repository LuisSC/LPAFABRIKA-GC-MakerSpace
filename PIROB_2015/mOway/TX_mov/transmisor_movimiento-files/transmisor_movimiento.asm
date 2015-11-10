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
adelante       EQU    0x7E 
girar          EQU    0x7D 
sensorLuz      EQU    0x7C 

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
  movwf    adelante
  movlw   .0
  movwf    girar
  movlw   .0
  movwf    sensorLuz

;************Module RfActivation****************************************

;***********************************************************************

;Configuration of SPI
  call	    RF_CONFIG_SPI

;Configuration of RF module (channel and dir)
  movlw	    .0		;Dir
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
;**************Module Assign Accelerometer******************************

;***********************************************************************
  call    SEN_ACCE_XYZ_READ
  movf    SEN_ACCE_Y,W
  movwf   adelante

;***********************************************************************
;**************Module Assign Accelerometer******************************

;***********************************************************************
  call    SEN_ACCE_XYZ_READ
  movf    SEN_ACCE_X,W
  movwf   girar

;***********************************************************************
;************Module RfTransmit********************************************

;***********************************************************************

  movlw       .1		;Dir of receptor
  movwf	    RF_DIR_OUT
			;Data to send		

  movf     adelante,W
  movwf	    RF_DATA_OUT_0
  movf     girar,W
  movwf	    RF_DATA_OUT_1
  movlw     .0
  movwf	    RF_DATA_OUT_2
  movlw     .0
  movwf	    RF_DATA_OUT_3
  movlw     .0
  movwf	    RF_DATA_OUT_4
  movlw     .0
  movwf	    RF_DATA_OUT_5
  movlw     .0
  movwf	    RF_DATA_OUT_6
  movlw     .0
  movwf	    RF_DATA_OUT_7

  call	    RF_SEND		;Send
  btfss	    RF_STATUS,SNDOK
  goto    label1
  btfss	    RF_STATUS,ACK	
  goto    label1


;***********************************************************************

label1:
;************Module Pause***********************************************

;***********************************************************************

  banksel	    AUX_00	 
  movlw   .20
  movwf   AUX_00
  call    Delay_50ms_mOwayGUI

;***********************************************************************


  goto    label0


  goto    label1

loopEnd:
  goto    loopEnd

END
