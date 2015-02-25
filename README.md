# Win-Fi
![Win-Fi Logo](/Win-Fi logo.png)

OS | License | Price
--- | --- | ---
Windows | MIT | Free


Win-Fi is VirtualWiFi, and free windows software to transform your PC internet connection into a WiFi hotspot.

You can easily create a WiFi hotspot to connect all your devices, just give your hotspot a name and password, and you are ready to go. 


### Manually setup

While Win-Fi help you to create hotspot but you can manually create it with netsh using CMD in windows

#### Setup new hotspot

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

#### Show users

To see the Hosted Network details & the connected users


```
    netsh wlan show hostednetwork
```

#### Change password


to change the network password

```
    netsh wlan refresh hostednetwork YourNewPassword
```

#### License

Win-Fi is licensed under the GNU GPL v2.0 License - see the LICENSE file for details

#### Contributing

Pull requests and issues are welcome.
