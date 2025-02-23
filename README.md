# Placar Eletrônico Interativo

## Autor
Projeto desenvolvido por **Giulia Domingues de Alcantara** como parte do **projeto final do curso da Embarcatech**.

## Sobre o Projeto
O **Placar Eletrônico Interativo** é um sistema embarcado que gerencia partidas através de um placar digital. Ele permite que o usuário defina a pontuação máxima da partida, inicie o jogo e registre os pontos de dois times (Time A e Time B). Quando um dos times atinge a pontuação pré-estabelecida, o sistema encerra automaticamente o jogo e exibe o vencedor. Essa solução é ideal para jogos, gincanas, interclasses e aulas de educação física.

## Objetivo
Desenvolver um dispositivo compacto e portátil, adequado para ambientes escolares, esportivos e recreativos, facilitando a gestão de partidas em diversas modalidades. O sistema otimiza o trabalho dos árbitros ao eliminar a necessidade de contagem manual e proporciona autonomia aos usuários para iniciar, registrar pontos e encerrar jogos de maneira eficiente.

## Principais Funcionalidades
- Permite configurar o número de pontos necessários para a definição do vencedor.
- Automatiza a contagem de pontos de uma partida de forma justa e imparcial.
- Apresenta o vencedor assim que a pontuação máxima for atingida.

## Descrição do Funcionamento
1. O usuário define a pontuação máxima da partida através de um menu intuitivo.
2. Após iniciar o jogo, os pontos são registrados através de botões específicos para cada equipe (Time A e Time B).
3. O display do placar atualiza os resultados em tempo real.
4. O design compacto permite fácil transporte e manuseio.
5. Quando um time atinge a pontuação máxima, o sistema encerra automaticamente o jogo e exibe o vencedor.

## Tecnologias Utilizadas
- **Microcontrolador:** [RaspberryPi Pico W - BitDogLab]
- **Display:** [Display OLED 0.96" I2C (128x64)]
- **Botões físicos ou sensores para entrada de dados**
- **Linguagem de programação:** [C]
- **Sistema Operacional:** [Linux / Windows + WSL]

## Como Usar
1. Ligue o dispositivo.
2. Configure a pontuação máxima desejada.
3. Inicie o jogo.
4. Registre os pontos dos times utilizando os botões disponíveis.
5. O sistema atualizará a pontuação em tempo real.
6. Ao atingir a pontuação máxima, o jogo será encerrado automaticamente e o vencedor será exibido.

## Manual de Configuração
### Pré-Requisitos
- **CMake**
- **Compilador C/C++ compatível**
- **Plataforma de desenvolvimento suportada pelo microcontrolador**

### Passos para Compilação e Instalação
1. Clone o repositório do projeto:
   ```sh
   git clone https://github.com/seu-repositorio/placar-eletronico.git
   cd placar-eletronico
   ```
2. Crie um diretório de build e acesse-o:
   ```sh
   mkdir build
   cd build
   ```
3. Gere os arquivos de build usando CMake:
   ```sh
   cmake ..
   ```
4. Compile o código:
   ```sh
   make
   ```
5. Envie o arquivo gerado para a placa:
   - Localize o arquivo gerado no diretório `build` com extensão `.uf2`.
   - Conecte a placa ao computador via USB.
   - Copie o arquivo `placar_eletronico.uf2` para a unidade correspondente à placa (normalmente detectada automaticamente no sistema operacional).
