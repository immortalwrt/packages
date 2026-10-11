Setting LTE/5G NSA/5G SA bands for selected modems.

Supported devices:
- BroadMobi BM806U
- Dell DW5821e Snapdragon X20 LTE (Foxconn T77W968)
- Dell DW5821e-eSIM Snapdragon X20 LTE
- Fibocom FG621-EA
- Fibocom FM350-GL
- Fibocom L850-GL
- Fibocom L850-GL in mbim mode
- Fibocom L860-GL
- Fibocom L860-GL-16
- Foxconn T99W175 (generic)
- HP lt4112 (Huawei ME906E)
- HP lt4132 LTE/HSPA+ 4G Module (Huawei ME906s-158)
- HP lt4220 (Foxconn T77W676)
- HP lt4220 (Foxconn T77W676) in mbim mode
- Huawei (various models) in serial mode
- Quectel EC20
- Quectel EC25
- Quectel EC200T-CN
- Quectel EG06-E
- Quectel EG12-EA
- Quectel EG18-EA
- Quectel EG120K-EA
- Quectel EM12-G
- Quectel EM12G-MSFT
- Quectel EM160R-GL
- Quectel EP06-A
- Quectel EP06-E
- Quectel RG500U-EB
- Quectel RG500Q-EA
- Quectel RG502Q-EA
- Quectel RM500Q-GL
- Quectel RM500U-CNV
- Quectel RM500U-EA
- Quectel RM500Q-AE
- Quectel RM502Q-AE
- Quectel RM502Q-GL
- Quectel RM505Q-AE
- Quectel RM520N-GL
- Quectel RM521F-GL
- Quectel RM551E-GL
- Sierra Wireless EM7455/MC7455/DW5811e
- SIMCOM SIM8200EA-M2
- Telit LM940
- Telit LN940 (Foxconn T77W676)
- Telit LN940 (Foxconn T77W676) in mbim mode
- Telit LN960 (Foxconn T77W968)
- Telit LN960
- Thales/Cinterion MV31-W (T99W175) in mbim mode
- Yuge CLM920 NC_5
- ZTE MF286 (router)
- ZTE MF286A (router)
- ZTE MF286D (router)
- ZTE MF286R (router)
- ZTE MF289R (router)

```
root@MiFi:~# modemband.sh help
Available commands:
 /usr/bin/modemband.sh getinfo
 /usr/bin/modemband.sh json
 /usr/bin/modemband.sh help

Manually specifying interface:
 DEVICE=/dev/ttyUSB2 /usr/bin/modemband.sh getinfo

for LTE modem
 /usr/bin/modemband.sh getsupportedbands
 /usr/bin/modemband.sh getsupportedbandsext
 /usr/bin/modemband.sh getbands
 /usr/bin/modemband.sh getbandsext
 /usr/bin/modemband.sh setbands "<band list>"

for 5G NSA modem
 /usr/bin/modemband.sh getsupportedbands5gnsa
 /usr/bin/modemband.sh getsupportedbandsext5gnsa
 /usr/bin/modemband.sh getbands5gnsa
 /usr/bin/modemband.sh getbandsext5gnsa
 /usr/bin/modemband.sh setbands5gnsa "<band list>"

for 5G SA modem
 /usr/bin/modemband.sh getsupportedbands5gsa
 /usr/bin/modemband.sh getsupportedbandsext5gsa
 /usr/bin/modemband.sh getbands5gsa
 /usr/bin/modemband.sh getbandsext5gsa
 /usr/bin/modemband.sh setbands5gsa "<band list>"

root@MiFi:~# # modemband.sh
Modem: Quectel EC25
Supported LTE bands: 1 3 5 7 8 20 38 40 41
LTE bands: 1 3 5 7 8 20 38 40 41 

 1: FDD 2100 MHz
 3: FDD 1800 MHz
 5: FDD  850 MHz
 7: FDD 2600 MHz
 8: FDD  900 MHz
20: FDD  800 MHz
38: TDD 2600 MHz
40: TDD 2300 MHz
41: TDD 2500 MHz

root@MiFi:~# modemband.sh json
{ "modem": "Quectel EC25", "supported": [ { "band": 1, "txt": "FDD 2100 MHz" }, { "band": 3, "txt": "FDD 1800 MHz" }, { "band": 5, "txt": "FDD  850 MHz" }, { "band": 7, "txt": "FDD 2600 MHz" }, { "band": 8, "txt": "FDD  900 MHz" }, { "band": 20, "txt": "FDD  800 MHz" }, { "band": 38, "txt": "TDD 2600 MHz" }, { "band": 40, "txt": "TDD 2300 MHz" }, { "band": 41, "txt": "TDD 2500 MHz" } ], "enabled": [ 1, 3, 5, 7, 8, 20, 38, 40, 41 ] }

root@MiFi:~# modemband.sh getinfo
Quectel EC25

root@MiFi:~# modemband.sh getsupportedbands
1 3 5 7 8 20 38 40 41

root@MiFi:~# modemband.sh getsupportedbandsext
 1: FDD 2100 MHz
 3: FDD 1800 MHz
 5: FDD  850 MHz
 7: FDD 2600 MHz
 8: FDD  900 MHz
20: FDD  800 MHz
38: TDD 2600 MHz
40: TDD 2300 MHz
41: TDD 2500 MHz

root@MiFi:~# modemband.sh getbands
1 3 5 7 8 20 38 40 41

root@MiFi:~# modemband.sh getbandsext
 1: FDD 2100 MHz
 3: FDD 1800 MHz
 5: FDD  850 MHz
 7: FDD 2600 MHz
 8: FDD  900 MHz
20: FDD  800 MHz
38: TDD 2600 MHz
40: TDD 2300 MHz
41: TDD 2500 MHz

root@MiFi:~# modemband.sh setbands "1 3 5 40"
at+qcfg="band",0,8000000015,0,1

root@MiFi:~# modemband.sh getbands
1 3 5 40

root@MiFi:~# modemband.sh setbands default
at+qcfg="band",0,1a0000800d5,0,1

root@MiFi:~# modemband.sh getbands
1 3 5 7 8 20 38 40 41
```

On ImmortalWrt, the `modemband.@modemband[0].set_port` UCI option still
overrides the automatically selected port. An explicit `DEVICE` environment
variable takes precedence over this option.

See also [description in Polish](https://eko.one.pl/?p=openwrt-modemband).

# Precompiled packages (ipk)

https://dl.eko.one.pl/packages/opkg/all/

# Precompiled packages (apk)

https://dl.eko.one.pl/packages/apk/noarch/

# The project is used in
- [easyconfig](https://eko.one.pl/?p=easyconfig) - [src](https://github.com/obsy/easyconfig)
- luci-app-modemband - [src](https://github.com/4IceG/luci-app-modemband)
