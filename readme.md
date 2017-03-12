# Minecraft server displaying the number of players (1-10) for DE1-SOC

- The hardware part is the same as in the example HPS_LED_HEX
- The software C part is different. If you want fast deployment, just go to the binaries_scripts files. Everyting is in it.
- WinSCP in good for doing file transfer. If you are using Linux, you can use scp line command tool. 

## Installation : 
- Download java embedded edition for armv7 http://www.oracle.com/technetwork/java/embedded/embedded-se/downloads/javase-embedded-downloads-2209751.html. 
- Put it on the de1-soc directory /usr/java
- Download Minecraft Server https://minecraft.net/en-us/download/server
- Put it on a new created directory : /home/root/Minecraft-111/
- Put the scripts and binairies on the git directory /home/root in the de1-soc directory /home/root/
- Put the git /etc/init.d/minecraft script on the de1-soc directory /etc/init.d/
- Type in a command line "update-rc.d minecraft enable"
- Reboot. All is OK. 

As I have done this guide very quickly, feel free to ask me at julien.levansuu@laposte.net
Sorry for the crappy code, but initially I didn't intent to publish this personnal project. 