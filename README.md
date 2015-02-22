# Win-Fi

WinFi is VirtualWiFi that helps you to transform your PC internet connection into a WiFi hotspot.

### Manually setup

While winfi help you to create hotspot but you can manually create it with netsh using CMD in windows

#### Setup net hotspot

Open your CMD app in windows as administrator then type:

```
    netsh wlan set hostednetwork mode=allow ssid=winfi key=shortshort
```

Where 'winfi' is your hotspot network name and 'shortshort' is the password or (WPA2-PSK key).

#### Enable hotspot

To start the hotspot type:

```
    netsh wlan start hostednetwork
```

#### Disable hotspot

To stop the hotspot type:


```
    netsh wlan start hostednetwork
```

#### Connected users

To see the Hosted Network details & the connected users


```
    netsh wlan show hostednetwork
```

#### Change password


to change the network password

```
    netsh wlan refresh hostednetwork YourNewPassword
```
