#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>

static struct timeval start_time;

void reset_time() {
    gettimeofday(&start_time, NULL);
}

double elapsed_time() {
    struct timeval end_time;
    gettimeofday(&end_time, NULL);

    double elapsed = (end_time.tv_sec - start_time.tv_sec) + 
                     ((end_time.tv_usec - start_time.tv_usec)/1000000.0);
    return elapsed;
}

// Define
#define FAN_PIN 3
#define MIN_TEMP 50
#define MAX_TEMP 55
#define CPU_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
#define MIN_PWM 0
#define MAX_PWM 100

int main() {
    int temp;
    float temp_ratio, pwm_ratio;
    int binary_val = 0;
    
    if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed\n");
        return 1;
    }
    
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, LOW);

    reset_time();
    
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
            if(elapsed_time() > 60 * 2){
                binary_val = 0;
                digitalWrite(FAN_PIN, LOW);
            }
        } else if (temp >= MAX_TEMP) {
            binary_val = 1;
            reset_time();
            digitalWrite(FAN_PIN, HIGH);
        }
        
        
        printf("CPU: %d°C | val: %d | Elapsed Time: %f\n", temp, binary_val, elapsed_time());
        
        sleep(5);
    }
    
    return 0;
}
