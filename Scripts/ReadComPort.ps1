# Define the COM port name and other settings
$portName = "COM8"  # Replace with your actual COM port
$baudRate = 115200
$dataBits = 8
$parity = "None"
$stopBits = "One"

$deviceName = "Aim-A-Lyzer"

# Create a new SerialPort object
$serialPort = New-Object System.IO.Ports.SerialPort

# Set the SerialPort properties
$serialPort.PortName = $portName
$serialPort.BaudRate = $baudRate
$serialPort.DataBits = $dataBits
$serialPort.Parity = $parity
$serialPort.StopBits = $stopBits


Write-Host "Starting COM port application"

#print list of all com ports
Get-WMIObject Win32_SerialPort | Select-Object DeviceID,Description,FriendlyName

# Function to open the SerialPort
function Open-SerialPort {
    $serialPort.Open()
    Write-Host "COM port opened"
}

# Function to close the SerialPort
function Close-SerialPort {
    if ($serialPort.IsOpen) {
        $serialPort.Close()
        Write-Host "COM port closed"
    }
}

# Continuous loop to monitor COM port status
while ($true) {
    # Check if the COM port is open
    if ($serialPort.IsOpen) {

        # Check if the device is still connected
        $deviceConnected = Get-PnpDevice | Where-Object { $_.FriendlyName -eq $deviceName -and $_.Status -eq 'OK' }

        if ($deviceConnected) {
            # Device is still connected, do nothing
        } else {
            # Device is disconnected, close the COM port
            Close-SerialPort
        }
    } else {

        Get-WMIObject Win32_SerialPort | Select-Object DeviceID,Description,PNPDeviceID, Status

        # Print out the list of PnP devices (for debugging)
        Write-Host "List of PnP Devices:"

        $pnpDevices | ForEach-Object { Write-Host "  $_.Name - $_.Status - $_.PNPDeviceID" }


        # Check if the device is connected
        $deviceConnected = Get-PnpDevice | Where-Object { $_.FriendlyName -eq $deviceName -and $_.Status -eq 'OK' }

        if ($deviceConnected) {
            # Device is connected, open the COM port
            Open-SerialPort
        } else {
            # Device is still disconnected, do nothing
        }
    }

    # Add a small delay to avoid high CPU usage
    Start-Sleep -Milliseconds 100
}

# Note: This loop will run indefinitely, so you may need to manually stop the script.
#       Consider adding a condition to exit the loop based on your specific requirements.
