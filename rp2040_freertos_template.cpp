/*
 * @brief Template de projeto para FreeRTOS no RP2040
 *
 * @author Carlos Delfino <consultoria@carlosdelfino.eti.br>
 * @version 0.1.0
 * @date 2025-11-26
 */
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "log_vt100.h"

// Função Principal
int main() {
  stdio_init_all();

  log_set_level(LOG_LEVEL_INFO);

  LOG_INFO("############################################");
  LOG_INFO("# RP2040 FreeRTOS Template                 #");
  LOG_INFO("# Versão: 0.1.0                            #");
  LOG_INFO("# Autor: Carlos Delfino                    #");
  LOG_INFO("# E-Mail: consultoria@carlosdelfino.eti.br #");
  LOG_INFO("# Data: 2025-11-26                         #");
  LOG_INFO("############################################");

  LOG_INFO("Contagem regressiva... ____");
  for (int i = 200; i > 0; i--) {
    LOG_INFO("\r\x1b[4C%04d", i);
    sleep_ms(1);
  }

  // Cria tasks FreeRTOS para cada funcionalidade
  LOG_INFO("[FreeRTOS] Criando tasks...");

  // Crie aqui suas tarefas com xTaskCreate

  LOG_INFO("[FreeRTOS] Iniciando scheduler...");
  vTaskStartScheduler();

  // Se chegar aqui, houve falha ao iniciar o scheduler
  for (;;) {
    tight_loop_contents();
  }
}

