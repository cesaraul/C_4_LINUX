# CESE 10ma Co Sistemas operativos de tiempo Real II
- Luis Lebus
- Ignacio Majul
- Cesar Cruz

## 1 pool de memoria

Add files via upload	8506012	imajul <55673926+imajul@users.noreply.github.com>	Mar 26, 2020 at 20:01
 ###  poolInit,poolDeinit,poolGet,poolPut


## 2 Uart Manager

 Add files via upload	15fbc8a	imajul <55673926+imajul@users.noreply.github.com>	Mar 27, 2020 at 15:01

 ### uartManagerInit,uartManagerDeinit,uartManagerGet,uartManagerPut,rxCallBack,txTask
 ### appInit, rxTask

## 3 CRC

Add files via upload	2883861	imajul <55673926+imajul@users.noreply.github.com>	Mar 27, 2020 at 15:01

### crc8_init,crc8_calc

## 4 pool de memoria update
Se pone en cero la memoria solicitada antes de entregarla, se asigna NULL al puntero principal luego de liberarlo	06e8794	Luis Lebus <luislebus@gmail.com>	Apr 3, 2020 at 06:37

## 5 uart Manager corrección de errores

### add onRxTimeoutCallback,onTxTimeoutCallback
