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
direccionTX    EQU    0x7D 
girar          EQU    0x7C 
sensorluz      EQU    0x7B 

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
  movwf    direccionTX
  movlw   .0
  movwf    girar
  movlw   .0
  movwf    sensorluz

;************Module Assigned********************************************

;***********************************************************************

  movlw   .127
  movwf   girar

;***********************************************************************
;************Module Assigned********************************************

;***********************************************************************

  movlw   .127
  movwf   adelante

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
  movwf    adelante
  movf     RF_DATA_IN_1,W
  movwf    girar

;***********************************************************************

;************Module Comparative*******************************************

;************************************************************************

  movf   girar,W
  addlw   .100
  btfss   STATUS,C
  goto    label1

;***********************************************************************
;**************Module Turn**********************************************

;***********************************************************************

  movlw   .50
  movwf       MOT_VEL
  bcf     MOT_CON,COMTYPE
  movlw   .12
  movwf   MOT_T_DIST_ANG
  movlw   0x01
  movwf   MOT_CENWHEEL
  bcf     MOT_CON,RL
  bsf     MOT_CON,FWDBACK
  call    MOT_ROT
  call    MOT_CHECK_END

;***********************************************************************


  goto    label0


label1:
;************Module Comparative*******************************************

;************************************************************************

  movf   girar,W
  addlw   .156
  btfsc   STATUS,C
  goto    label2

;***********************************************************************
;**************Module Turn**********************************************

;***********************************************************************

  movlw   .50
  movwf       MOT_VEL
  bcf     MOT_CON,COMTYPE
  movlw   .12
  movwf   MOT_T_DIST_ANG
  movlw   0x01
  movwf   MOT_CENWHEEL
  bsf     MOT_CON,RL
  bsf     MOT_CON,FWDBACK
  call    MOT_ROT
  call    MOT_CHECK_END

;***********************************************************************


  goto    label0


label2:
;************Module Comparative*******************************************

;************************************************************************

  movf   adelante,W
  addlw   .156
  btfsc   STATUS,C
  goto    label3

;***********************************************************************
;************Module Move*************************************************

;***********************************************************************

  movlw   .50
  movwf   MOT_VEL
  bsf     MOT_CON,COMTYPE
  movlw   .0
  movwf   MOT_T_DIST_ANG
  bsf     MOT_CON,FWDBACK
  call    MOT_STR

;***********************************************************************


  goto    label0


label3:
;************Module Comparative*******************************************

;************************************************************************

  movf   adelante,W
  addlw   .100
  btfss   STATUS,C
  goto    label4

;***********************************************************************
;************Module Move*************************************************

;***********************************************************************

  movlw   .50
  movwf   MOT_VEL
  bsf     MOT_CON,COMTYPE
  movlw   .0
  movwf   MOT_T_DIST_ANG
  bcf     MOT_CON,FWDBACK
  call    MOT_STR

;***********************************************************************


  goto    label0


label4:
;************Module Stop************************************************

;***********************************************************************

;   Call STOP 
    call    MOT_STOP

;***********************************************************************


  goto    label0

loopEnd:
  goto    loopEnd

END
