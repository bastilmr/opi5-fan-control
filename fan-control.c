#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

// Define
#define FAN_PIN 3
#define MIN_TEMP 30
#define MAX_TEMP 70
#define CPU_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
#define MIN_PWM 0
#define MAX_PWM 100

int main() {
    int temp;
    float temp_ratio, pwm_ratio;
    int pwm_value = 0;
    
    if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed\n");
        return 1;
    }
    
    pinMode(FAN_PIN, OUTPUT);
    softPwmCreate(FAN_PIN, MIN_PWM, MAX_PWM);
    
    while(1) {
        FILE* temp_file = fopen(CPU_TEMP_FILE, "r");
        
        if (temp_file == NULL) {
            printf("Failed to read CPU temperature file\n");
            return 1;
        }
        
        fscanf(temp_file, "%d", &temp);
        fclose(temp_file);
        
        temp /= 1000;
        
        if (temp < MIN_TEMP) {
            pwm_value = MIN_PWM;
        } else if (temp > MAX_TEMP) {
            pwm_value = MAX_PWM;
        } else {
            temp_ratio = (float)(temp - MIN_TEMP) / (MAX_TEMP - MIN_TEMP);
            pwm_ratio = temp_ratio * (MAX_PWM - MIN_PWM);
            pwm_value = (int)(pwm_ratio + MIN_PWM);
        }
        
        softPwmWrite(FAN_PIN, pwm_value);
        
        printf("CPU: %d°C | PWM: %d%%\n", temp, pwm_value);
        
        sleep(5);
    }
    
    return 0;
}
