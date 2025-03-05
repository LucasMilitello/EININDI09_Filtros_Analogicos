# Especificação de um filtro analógico Butterworth partindo de uma Frequência limite.

Este README.md reúne uma explicação detalhada, tanto matemática quanto prática, de uma função Python que calcula um filtro Butterworth analógico e plota a sua resposta em frequência a partir de uma Frequência limite. A função destaca pontos importantes como a frequência limite da banda de interesse (passagem ou rejeição), a frequência de corte calculada e a frequência desejada definida pelo usuário.

---

## 1. Explicação Matemática e Conceitual

### Conversão da Frequência Desejada

A frequência desejada é fornecida em Hertz (Hz) e deve ser convertida para radianos por segundo (rad/s) para que os cálculos estejam em unidades compatíveis com a análise de filtros analógicos. A conversão é feita pela seguinte fórmula:

$$
\omega_d = 2\pi\, f_{\text{desejada}}
$$

---

### Definição da Magnitude Alvo ($M_{\text{target}}$)

Dependendo da banda de interesse, define-se:
- **Banda de Passagem** ($isBP = \text{True}$):  
  $$ M_{\text{target}} = 1 - \text{desvio} $$
- **Banda de Rejeição** ($isBP = \text{False}$):  
  $$ M_{\text{target}} = \text{desvio} $$

---

### Filtro Butterworth Passa-Baixa

A resposta em frequência de um filtro Butterworth passa-baixa é dada por:

$$
|H(j\omega)| = \frac{1}{\sqrt{1 + \left(\frac{\omega}{\omega_c}\right)^{2n}}}
$$

Queremos que, na frequência de transição ($\omega_{\text{edge}}$), a magnitude seja igual a $M_{\text{target}}$. Assim:

$$
\frac{1}{\sqrt{1 + \left(\frac{\omega_{\text{edge}}}{\omega_c}\right)^{2n}}} = M_{\text{target}}
$$

Elevando ao quadrado e isolando o termo com $\omega_{\text{edge}}$, temos:

$$
\left(\frac{\omega_{\text{edge}}}{\omega_c}\right)^{2n} = \frac{1}{M_{\text{target}}^2} - 1
$$

Extraindo a raiz:

$$
\frac{\omega_{\text{edge}}}{\omega_c} = \left(\frac{1}{M_{\text{target}}^2} - 1\right)^{\frac{1}{2n}}
$$

Definindo:

$$
A = \left(\frac{1}{M_{\text{target}}^2} - 1\right)^{\frac{1}{2n}}
$$

Temos, então:

$$
\omega_{\text{edge}} = \omega_c \cdot A
$$

Para posicionar a frequência desejada corretamente:
- Se a frequência desejada deve estar na **banda de passagem** ($isBP = \text{True}$), usamos:
  
$$
\omega_{\text{edge}} = \omega_d \times (1 + \epsilon)
$$

  (pois desejamos que $\omega_d < \omega_{\text{edge}}$);
  
- Se estiver na **banda de rejeição** ($isBP = \text{False}$), usamos:
  
$$
\omega_{\text{edge}} = \omega_d \times (1 - \epsilon)
$$

  (pois desejamos que $\omega_d > \omega_{\text{edge}}$).

Finalmente, a frequência de corte é obtida por:

$$
\omega_c = \frac{\omega_d \times (1 + \epsilon)}{A}, (isBP = \text{True})
$$

ou 

$$
\omega_c = \frac{\omega_d \times (1 - \epsilon)}{A}, (isBP = \text{False})
$$
---

### Filtro Butterworth Passa-Alta

A resposta do filtro passa-alta é dada por:

$$
|H(j\omega)| = \frac{1}{\sqrt{1 + \left(\frac{\omega_c}{\omega}\right)^{2n}}}
$$

Na frequência de transição ($\omega_{\text{edge}}$), impõe-se:

$$
\frac{1}{\sqrt{1 + \left(\frac{\omega_c}{\omega_{\text{edge}}}\right)^{2n}}} = M_{\text{target}}
$$

Elevando ao quadrado e isolando $\omega_c$:

$$
\left(\frac{\omega_c}{\omega_{\text{edge}}}\right)^{2n} = \frac{1}{M_{\text{target}}^2} - 1
$$

Extraindo a raiz:

$$
\frac{\omega_c}{\omega_{\text{edge}}} = \left(\frac{1}{M_{\text{target}}^2} - 1\right)^{\frac{1}{2n}} = A
$$

Portanto:

$$
\omega_{\text{edge}} = \frac{\omega_c}{A}
$$

E, ajustando o posicionamento:
- Para **banda de passagem** ($isBP = \text{True}$) em passa-alta, desejamos que $\omega_d > \omega_{\text{edge}}$, então:

$$
\omega_{\text{edge}} = \omega_d \times (1 - \epsilon)
$$

- Para **banda de rejeição** ($isBP = \text{False}$):

$$
\omega_{\text{edge}} = \omega_d \times (1 + \epsilon)
$$

Logo, a frequência de corte é:

$$
\omega_c = \omega_d \times (1 + \epsilon) \cdot A , (isBP = \text{False})
$$

ou 

$$
\omega_c = \omega_d \times (1 - \epsilon) \cdot A , (isBP = \text{True})
$$

---

### Conversão para Hertz e Plotagem

Após calcular $\omega_c$ (em rad/s), converte-se para Hz:

$$
f_c = \frac{\omega_c}{2\pi}
$$

O gráfico da resposta do filtro é gerado e marca:
- **Linha Vermelha (tracejada)**: A frequência limite da banda de interesse (banda de passagem ou rejeição), ou seja, $\omega_{\text{edge}}$ convertido para Hz.
- **Linha Verde (tracejada)**: A frequência de corte calculada, $f_c$.
- **Linha Amarela (tracejada)**: A frequência desejada, $f_{\text{desejada}}$.

---

## 2. Explicação Prática da Função

### O que a Função Recebe

A função `calcular_e_plotar_filtro_analogico` recebe os seguintes parâmetros:

```python 

- **fDesejada**: Frequência desejada (em Hz) para a banda de interesse.  
  *Exemplo: 1000 Hz.*
- **ordem**: Ordem do filtro, ou seja, o número de polos.  
  *Exemplo: 2 (um filtro de segunda ordem).*
- **filterType**: Tipo do filtro – `'lowpass'` para filtro passa-baixa ou `'highpass'` para filtro passa-alta.  
  *Exemplo: `'lowpass'`.*
- **desvio**: Valor do desvio máximo permitido na magnitude da resposta do filtro.  
  *Exemplo: 0.05 (representa 5% de desvio).*
- **isBP**: Booleano que indica se a frequência desejada está na banda de passagem (`True`) ou na banda de rejeição (`False`).  
  *Exemplo: `True` se a frequência desejada deve estar na banda de passagem.*
```

### O que a Função Faz

1. **Conversão de Unidades**:  
   Converte a frequência desejada de Hz para rad/s.

2. **Definição da Magnitude Alvo**:  
   Define $M_{\text{target}}$ com base em se a frequência desejada deve estar na banda de passagem ou rejeição.

3. **Cálculo da Frequência de Transição e de Corte**:  
   Utilizando as equações do filtro Butterworth, a função calcula:
   - A frequência limite ($\omega_{\text{edge}}$) onde a magnitude atinge $M_{\text{target}}$, aplicando um ajuste pequeno (fator $\epsilon$) para posicionar corretamente a frequência desejada.
   - A frequência de corte ($\omega_c$) a partir de $\omega_{\text{edge}}$ e do fator $A$.
   
4. **Conversão para Hertz**:  
   Converte $\omega_c$ de rad/s para Hz.

5. **Plotagem do Gráfico**:  
   Gera um gráfico da resposta em frequência do filtro Butterworth e plota:
   
``` 
- A **curva azul** representando a resposta do filtro.  
- Uma **linha vermelha (tracejada)** indicando a frequência limite da banda (passagem ou rejeição).  
- Uma **linha verde (tracejada)** indicando a frequência de corte calculada.  
- Uma **linha amarela (tracejada)** indicando a frequência desejada.
```

6. **Retorno da Função**:  
   A função retorna a frequência de corte escolhida (em Hz), permitindo seu uso em análises posteriores.

---

## 3. Código Completo

A seguir, o código que integra todas as etapas descritas:

```python 

import numpy as np
import matplotlib.pyplot as plt

def calcular_e_plotar_filtro_analogico(fDesejada, ordem, filterType, desvio, isBP):
    """
    Calcula a frequência de corte (omega_c) de um filtro analógico Butterworth, 
    plota a resposta em frequência com as linhas que indicam:
      - A frequência limite da banda de interesse (passagem ou rejeição)
      - A frequência de corte escolhida
      - A frequência desejada
    e retorna a frequência de corte em Hz.
    """
    # Converte a frequência desejada de Hz para rad/s
    omega_d = 2 * np.pi * fDesejada

    # Define a magnitude alvo conforme a banda de interesse:
    # - Banda de passagem: 1 - desvio
    # - Banda de rejeição: desvio
    M_target = 1 - desvio if isBP else desvio

    # Pequeno ajuste para garantir que fDesejada fique do lado correto da transição
    epsilon = 1e-6

    # Cálculo de omega_c e omega_edge conforme o tipo de filtro
    A = ((1 / (M_target**2)) - 1)**(1/(2*ordem))
    if filterType.lower() == 'lowpass':
        if isBP:
            # Para banda de passagem, ω_d deve ser menor que ω_edge
            omega_edge = omega_d * (1 + epsilon) 
        else:
            # Para banda de rejeição, ω_d deve ser maior que ω_edge
            omega_edge = omega_d * (1 - epsilon)
        omega_c = omega_edge / A
    elif filterType.lower() == 'highpass':
        if isBP:
            # Para passa-alta, banda de passagem: ω_d deve ser maior que ω_edge
            omega_edge = omega_d * (1 - epsilon)
        else:
            # Para passa-alta, banda de rejeição: ω_d deve ser menor que ω_edge
            omega_edge = omega_d * (1 + epsilon)
        omega_c = omega_edge * A
    else:
        raise ValueError("filterType deve ser 'lowpass' ou 'highpass'.")

    # Converte as frequências de rad/s para Hz
    fc_escolhido_hz = omega_c / (2 * np.pi)
    freq_limite = omega_edge / (2 * np.pi)

    # Define a faixa de frequências para o gráfico
    f_min = fDesejada / 10 if filterType.lower() == 'highpass' else 0
    f_max = max(fDesejada, fc_escolhido_hz, freq_limite) * 1.5
    freqs = np.linspace(f_min, f_max, 500)
    w = 2 * np.pi * freqs  # Converte para rad/s

    # Calcula a resposta em frequência do filtro Butterworth
    if filterType.lower() == 'lowpass':
        H = 1 / np.sqrt(1 + (w / omega_c)**(2 * ordem))
    else:  # highpass
        H = 1 / np.sqrt(1 + (omega_c / w)**(2 * ordem))

    # Cria o gráfico da resposta em frequência
    fig, ax = plt.subplots(figsize=(8, 5))
    ax.plot(freqs, H, label='Resposta do Filtro', color='b')
    ax.set_xlabel('Frequência (Hz)')
    ax.set_ylabel('Magnitude')
    ax.set_title('Resposta em Frequência do Filtro Butterworth')

    # Plota a linha vertical da frequência limite (banda de passagem ou rejeição)
    if isBP:
        print("Frequência limite da Banda de Passagem [Vermelho]:", freq_limite)
        ax.axvline(freq_limite, color='r', linestyle='--', label='Banda de Passagem')
    else:
        print("Frequência limite da Banda de Rejeição [Vermelho]:", freq_limite)
        ax.axvline(freq_limite, color='r', linestyle='--', label='Banda de Rejeição')

    # Plota a linha vertical da frequência de corte escolhida
    print("Frequência de Corte [Verde]:", fc_escolhido_hz)
    ax.axvline(fc_escolhido_hz, color='g', linestyle='--', label='Frequência de Corte')

    # Plota a linha vertical da frequência desejada
    print("Frequência Desejada [Amarelo]:", fDesejada)
    ax.axvline(fDesejada, color='y', linestyle='--', label='Frequência Desejada')

    ax.grid(True)
    ax.legend()
    plt.show()

    return fc_escolhido_hz

if __name__ == '__main__':
    fDesejada = 1000   # Frequência desejada em Hz
    ordem = 2
    filterType = 'lowpass'  # 'lowpass' ou 'highpass'
    desvio = 0.05      # 5% de desvio
    isBP = True        # True para banda de passagem; False para rejeição

    fc = calcular_e_plotar_filtro_analogico(fDesejada, ordem, filterType, desvio, isBP)
    print("Frequência de Corte escolhida (Hz):", fc)
```

---

## Conclusão

A função `calcular_e_plotar_filtro_analogico`:
- Recebe parâmetros que definem as características do filtro (frequência desejada, ordem, tipo, desvio e a posição da banda).
- Converte a frequência desejada para rad/s, define a magnitude alvo e, a partir das equações do filtro Butterworth, calcula a frequência de transição e a frequência de corte.
- Plota a resposta em frequência do filtro com marcações (linha vermelha para a frequência limite, linha verde para a frequência de corte e linha amarela para a frequência desejada) que facilitam a visualização e análise.
- Retorna a frequência de corte em Hz para utilização em análises ou projetos subsequentes.

Este README detalha tanto a base teórica quanto a implementação prática da função, permitindo uma compreensão completa e a possibilidade de adaptações conforme necessário.
