# Win-Fi

WinFi is VirtualWiFi that helps you to transform your PC internet connection into a WiFi hotspot.

## Manually setup

While winfi help you to create hotspot but you can manually created with netsh

```
    netsh wlan set hostednetwork mode=allow ssid=winfi key=shortshort
```

Where 'winfi' is your hotspot network name and 'shortshort' is the password or (WPA2-PSK key).

### To start the hotspot:

```
    netsh wlan start hostednetwork
```

### To stop the hotspot:

```
    netsh wlan start hostednetwork
```

### To see the Hosted Network details & the connected users

```
    netsh wlan show hostednetwork
```

### to change the password

```
    netsh wlan refresh hostednetwork YourNewPassword
```
