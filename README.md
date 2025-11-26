# RP2040 FreeRTOS Template

[![Build](https://img.shields.io/github/actions/workflow/status/ArvoreDosSaberes/rp2040_freertos_template/ci.yml?branch=main)](https://github.com/ArvoreDosSaberes/rp2040_freertos_template/actions)
[![Issues](https://img.shields.io/github/issues/ArvoreDosSaberes/rp2040_freertos_template)](https://github.com/ArvoreDosSaberes/rp2040_freertos_template/issues)
[![Stars](https://img.shields.io/github/stars/ArvoreDosSaberes/rp2040_freertos_template)](https://github.com/ArvoreDosSaberes/rp2040_freertos_template/stargazers)
[![Forks](https://img.shields.io/github/forks/ArvoreDosSaberes/rp2040_freertos_template)](https://github.com/ArvoreDosSaberes/rp2040_freertos_template/network/members)
[![Visitors](https://komarev.com/ghpvc/?username=ArvoreDosSaberes&repo=rp2040_freertos_template&color=blue&style=flat)](https://github.com/ArvoreDosSaberes/rp2040_freertos_template)
[![License: CC BY 4.0](https://img.shields.io/badge/license-CC%20BY%204.0-blue.svg)](https://creativecommons.org/licenses/by/4.0/)


---

## Visão geral

Este projeto é um **template para firmware com FreeRTOS no RP2040 (Pico/Pico W)**, preparado para ser renomeado e reutilizado como base de novos firmwares.

O arquivo principal de aplicação é:

- `rp2040_freertos_template.cpp`

A configuração de build é centralizada em:

- `CMakeLists.txt`

A árvore de tasks do FreeRTOS fica organizada em:

- `tasks/`

A licença utilizada é **Creative Commons Attribution 4.0 International (CC BY 4.0)**, conforme arquivo [`LICENSE`](LICENSE).

---

## Importante: evitar espaços no caminho do projeto

Para evitar problemas de CMake, toolchain e scripts, **não utilize espaços no path** onde o projeto é clonado/compilado. Por exemplo, prefira caminhos como:

- `/home/usuario/workspace/Projeto_Final/RP2040_FreeRTOS_Template`

e **evite** caminhos como:

- `/home/usuario/Meus Projetos/Projeto Final/RP2040 FreeRTOS Template`

Algumas ferramentas não lidam bem com espaços em diretórios, o que pode causar erros difíceis de diagnosticar.

---

## Processo de renomeação do template para um novo projeto

Ao criar um novo firmware baseado neste template, siga os passos abaixo para renomear tudo de forma consistente.

### 1. Escolha o nome do projeto

Defina um nome **sem espaços**, em inglês e em `snake_case` ou `lowercase` simples, por exemplo:

- `rack_intelligent_controller`
- `environment_monitor`

Neste README vamos usar o exemplo **`rack_intelligent_controller`**.

### 2. Renomear o arquivo principal

1. Localize o arquivo:
   - `rp2040_freertos_template.cpp`
2. Renomeie para o nome do projeto, por exemplo:
   - `rack_intelligent_controller.cpp`

### 3. Atualizar o `CMakeLists.txt` da raiz

Abra o arquivo `CMakeLists.txt` na raiz e procure pelas referências a `rp2040_freertos_template`. Neste template, os pontos principais são:

- Definição do nome do projeto:
  - `set(ProjectName rp2040_freertos_template)`
  - `project(rp2040_freertos_template C CXX ASM)`
- Criação do executável:
  - `add_executable(rp2040_freertos_template rp2040_freertos_template.cpp)`
- Metadados do programa:
  - `pico_set_program_name(rp2040_freertos_template "rp2040_freertos_template")`
  - `pico_set_program_version(rp2040_freertos_template "0.1")`
- Configurações de STDIO:
  - `pico_enable_stdio_uart(rp2040_freertos_template 0)`
  - `pico_enable_stdio_usb(rp2040_freertos_template 1)`
- Bibliotecas e includes:
  - `target_link_libraries(rp2040_freertos_template ...)`
  - `link_freertos(rp2040_freertos_template)`
  - `target_include_directories(rp2040_freertos_template ...)`
  - `target_link_libraries(rp2040_freertos_template ...)`
  - `target_compile_definitions(rp2040_freertos_template PRIVATE ...)`
  - `pico_add_extra_outputs(rp2040_freertos_template)`

Substitua **todas** as ocorrências de `rp2040_freertos_template` pelo novo nome do projeto. Seguindo o exemplo, ficaria algo como:

- `set(ProjectName rack_intelligent_controller)`
- `project(rack_intelligent_controller C CXX ASM)`
- `add_executable(rack_intelligent_controller rack_intelligent_controller.cpp)`
- `pico_set_program_name(rack_intelligent_controller "rack_intelligent_controller")`
- Demais chamadas (`pico_enable_stdio_*`, `target_link_libraries`, `link_freertos`, etc.) também devem usar `rack_intelligent_controller`.

> **Dica:** Use a função de "Substituir em arquivos" do seu editor/IDE para garantir que não fique nenhuma referência antiga.

### 4. Renomear projetos e libs relacionadas

Caso existam outros `CMakeLists.txt` com referências a `rp2040_freertos_template` (por exemplo, em subdiretórios de `tasks/` ou `lib/`), repita o mesmo procedimento, atualizando:

- Nomes de alvo de biblioteca ou executável.
- Dependências de `target_link_libraries`.
- Qualquer `add_dependencies` ou macros específicas que façam referência ao nome antigo.

Mantenha uma **coerência total**: o nome do executável principal, do projeto CMake e das bibliotecas relacionadas deve refletir o novo nome do projeto.

---

## Como funciona a criação de tarefas FreeRTOS neste template

### 1. Estrutura geral

Este template organiza as funcionalidades em **tasks FreeRTOS**, cada uma responsável por um conjunto de responsabilidades (rede, sensores, MQTT, interface, etc.).

No arquivo principal atualmente (`rp2040_freertos_template.cpp`), as tasks são criadas dentro da função `main()` usando `xTaskCreate(...)`. Exemplos:

- `vNetworkPollTask` – monitora a rede / Wi-Fi.
- `vTiltTask` – leitura de sensor de inclinação.
- `vTemperatureHumidityTask` – leitura de temperatura/umidade.
- `vGpsTask` – leitura do módulo GPS.
- `keyboard_task` – leitura do teclado.
- `vMenuOledTask` – atualização de menu na tela OLED.
- Tasks `*_mqtt_task` – publicação de dados via MQTT.
- `vSignsOnTask` – task de _sign-on_ e status geral.

O padrão utilizado é:

```c
xTaskCreate(
    taskFunction,              // Função da task (implementada em outro módulo)
    "task_name",              // Nome textual da task
    STACK_SIZE_CONSTANT,       // Tamanho da stack (constante definida em header)
    pvParameters,              // Parâmetro passado para a task (pode ser NULL)
    PRIORITY_CONSTANT,         // Prioridade (constante de configuração)
    NULL                       // Handle da task (opcional, pode ser guardado)
);
```

### 2. Onde implementar novas tasks

As tasks costumam ser implementadas em arquivos separados dentro de `tasks/`, por exemplo:

- `gps_task.h` / `gps_task.c(pp)`
- `keyboard_task.h` / `keyboard_task.c(pp)`
- `door_state_task.h` / etc.

O fluxo recomendado para criar uma **nova task** é:

1. **Criar o par de arquivos** no diretório `tasks/` (por exemplo `my_feature_task.h` e `my_feature_task.c` ou `.cpp`).
2. **Declarar a função de task** no header, por exemplo:
   ```c
   #ifdef __cplusplus
   extern "C" {
   #endif

   void vMyFeatureTask(void *pvParameters);

   #ifdef __cplusplus
   }
   #endif
   ```
3. **Implementar a função de task** no `.c`/`.cpp` usando o laço padrão do FreeRTOS:
   ```c
   void vMyFeatureTask(void *pvParameters) {
       for (;;) {
           // 1. Ler sensores / estado
           // 2. Processar dados
           // 3. Publicar em filas, event groups ou MQTT
           // 4. Aguardar período adequado
           vTaskDelay(pdMS_TO_TICKS(MY_FEATURE_PERIOD_MS));
       }
   }
   ```
4. **Configurar o build** da nova task no `tasks/CMakeLists.txt`, adicionando o novo arquivo à biblioteca/target de `tasks`.
5. **Incluir o header da task** no arquivo principal (`rp2040_freertos_template.cpp` ou no novo nome do projeto) e chamar `xTaskCreate(...)` no `main()`.

### 3. Boas práticas ao criar tasks

- **Uma responsabilidade por task**: cada task deve ter um propósito bem definido (ex.: somente leitura de sensor, somente comunicação, somente interface).
- **Comunicação via filas/event groups**: evite compartilhar variáveis globais sem proteção. Utilize `queues`, `event groups` e `semaphores`.
- **Delays bem definidos**: use `vTaskDelay` ou `vTaskDelayUntil` para dar tempo ao scheduler e evitar _busy-wait_.
- **Stack size mínimo necessário**: use constantes de stack (`*_STACK_SIZE`) ajustadas ao consumo real da task para economizar RAM.
- **Prioridades consistentes**: defina prioridades em um header central (por exemplo, `rack_inteligente_parametros.h`) para manter visibilidade do modelo de escalonamento.

### 4. Fluxo de inicialização até o `vTaskStartScheduler()`

O `main()` deste template segue aproximadamente o fluxo:

1. Inicialização de `stdio`, logs e contagem regressiva.
2. Configuração de Wi-Fi (`cyw43_arch_init`, conexão à rede).
3. Inicialização de barramento I2C e OLED.
4. Criação de **event groups** (por exemplo, `create_event_group()`, `create_menu_event_group()`).
5. Configuração de GPIOs (ex.: estado da porta, interrupções).
6. Configuração de MQTT (cliente, tópico base, DNS do broker, callbacks).
7. **Criação das tasks FreeRTOS** com `xTaskCreate(...)` para cada funcionalidade.
8. Chamada de `vTaskStartScheduler()` para iniciar o escalonador do FreeRTOS.

Após `vTaskStartScheduler()`, em operação normal, o código **não retorna** ao `main()`. Se retornar, indica falha ao iniciar o scheduler.

---

## Licença

Este projeto (código-fonte e documentação) está licenciado sob a
**Creative Commons Attribution 4.0 International (CC BY 4.0)**.

Você pode copiar, modificar e utilizar este template, inclusive para
fins comerciais, desde que **cite explicitamente a autoria** e mantenha
referência à licença original. Consulte o arquivo [`LICENSE`](LICENSE)
e o texto oficial em https://creativecommons.org/licenses/by/4.0/ para
mais detalhes.
