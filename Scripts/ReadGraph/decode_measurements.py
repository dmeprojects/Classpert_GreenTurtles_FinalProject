import os
import matplotlib.pyplot as plt

def read_imu_data(file_path):
    data = {'measurement': [], 'system_tick': [], 'accelerometer': {'x': [], 'y': [], 'z': []}, 'gyroscope': {'x': [], 'y': [], 'z': []}, 'temperature': []}

    with open(file_path, 'r') as file:
        for line in file:
            print("line read: ")
            print(line)
            components = line.strip().split('|')
            data['measurement'].append(int(components[0]))
            data['system_tick'].append(int(components[1]))
            
            accel_values = list(map(int, components[2].split(';')))
            data['accelerometer']['x'].append(accel_values[0])
            data['accelerometer']['y'].append(accel_values[1])
            data['accelerometer']['z'].append(accel_values[2])
            
            gyro_values = list(map(int, components[3].split(';')))
            data['gyroscope']['x'].append(gyro_values[0])
            data['gyroscope']['y'].append(gyro_values[1])
            data['gyroscope']['z'].append(gyro_values[2])
            
            data['temperature'].append(float(components[4]))

    return data

def plot_imu_data(data, file_name):
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True, figsize=(10, 6))

    ax1.plot(data['system_tick'], data['accelerometer']['x'], label='X-axis')
    ax1.plot(data['system_tick'], data['accelerometer']['y'], label='Y-axis')
    ax1.plot(data['system_tick'], data['accelerometer']['z'], label='Z-axis')
    ax1.set_title(f'Accelerometer Values ({file_name})')
    ax1.set_ylabel('Acceleration')
    ax1.legend()

    ax2.plot(data['system_tick'], data['gyroscope']['x'], label='X-axis')
    ax2.plot(data['system_tick'], data['gyroscope']['y'], label='Y-axis')
    ax2.plot(data['system_tick'], data['gyroscope']['z'], label='Z-axis')
    ax2.set_title(f'Gyroscope Values ({file_name})')
    ax2.set_ylabel('Angular Velocity')
    ax2.set_xlabel('System Tick Time')
    ax2.legend()


    plt.tight_layout()  
    
    plt.get_current_fig_manager().set_window_title(file_name) 
    
    plt.show()

if __name__ == "__main__":
    file_path = r'D:\Github\Classpert_GreenTurtles_FinalProject\Scripts\ReadGraph\meas_files\MEASUREMENT_004.txt'  # Replace with the actual path to your file    
    imu_data = read_imu_data(file_path)
    file_name = os.path.basename(file_path)
    print(file_name)
    graph_name = file_name.split('.')[0]
    
    plot_imu_data(imu_data, file_name)