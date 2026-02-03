#include <pthread.h>
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define CHIP_NAME "/dev/gpiochip0"
#define LINE_NUM 17

static void *gpio_interrupt_thread(void *arg);

int main() {
    pthread_t tid;
    pthread_create(&tid, 0, gpio_interrupt_thread, 0);

    while (1)
    {
        printf("[Main] Running.......\n");
        sleep(1);
    }

    pthread_cancel(tid);
    pthread_join(tid, NULL);

    return 0;
}

static void *gpio_interrupt_thread(void *arg)
{
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    struct gpiod_line_event event;
    int ret;

    chip = gpiod_chip_open(CHIP_NAME);
    line = gpiod_chip_get_line(chip, LINE_NUM);
    gpiod_line_request_both_edges_events(line, "gpio_thread");

    printf("[Thread] Listening for GPIO%d events...\n", LINE_NUM);
    while (1)
    {
        ret = gpiod_line_event_wait(line, NULL);
        if (ret > 0)
        {
            gpiod_line_event_read(line, &event);
            if (event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE)
                printf("[Thread] Interrupt detected!\n");
        }
    }
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return NULL;
}
