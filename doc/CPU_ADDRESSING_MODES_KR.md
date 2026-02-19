# CPU ADDRMode

> 원본: https://www.nesdev.org/wiki/CPU_addressing_modes

---

NES CPU는 리코(Ricoh)가 제조한 MOS Technology 6502의 세컨드 소스 버전이다. ADDRMode와 명령어 타이밍은 표준 6502와 동일하다.

이 페이지는 6502 ADDRMode를 요약하고, 특정 모드가 유용한 경우를 설명한다.

---

## Indexed addressing

Indexed ADDRMode는 X 또는 Y 레지스터를 사용하여 주소를 결정하는 데 도움을 준다.
6502에는 6가지 주요 Indexed ADDRMode가 있다:

| 약어  | 이름                   | 공식                                                                      | 사이클 |
| ----- | ---------------------- | ------------------------------------------------------------------------- | ------ |
| d,x   | Zero Page Indexed      | `val = PEEK((arg + X) % 0xFF)                                           ` | 4      |
| d,y   | Zero Page Indexed      | `val = PEEK((arg + Y) % 0xFF)                                           ` | 4      |
| a,x   | Absolute Indexed       | `val = PEEK(arg + X)                                                    ` | 4+     |
| a,y   | Absolute Indexed       | `val = PEEK(arg + Y)                                                    ` | 4+     |
| (d,x) | Indexed Indirect (..!) | `val = PEEK(PEEK((arg + X) % 0xFF) + PEEK((arg + X + 1) % 0xFF) * 0xFF) ` | 6      |
| (d),y | Indirect Indexed (..!) | `val = PEEK(PEEK(arg) + PEEK((arg + 1) % 0xFF) * 0xFF + Y)              ` | 5+     |

참고:

- ADDRMode 약어는 WDC의 65C816 데이터시트에서 사용되는 것을 따른다.
- **+** 는 쓰기 명령어이거나 읽기 명령어에서 페이지 래핑이 발생하면 1사이클을 추가한다는 뜻이며, 아래에서 "oops" 사이클이라고 부른다.

6502에는 8비트 ALU 하나와 16비트 업카운터(PC용) 하나가 있다. STA, STX, STY가 아닌 명령어에서 a,x 또는 a,y 어드레싱을 계산할 때, 8비트 ALU로 먼저 하위 바이트를 계산하면서 동시에 상위 바이트를 페치한다. 캐리 아웃이 발생하면 "oops"하고, ALU를 사용하여 캐리를 적용한 뒤, 올바른 주소에서 읽기를 반복한다. 쓰기(Store) 명령어는 항상 이 "oops" 사이클을 가진다: CPU가 먼저 부분적으로 더해진 주소에서 읽기를 하고, 그 다음 올바른 주소에 쓰기를 한다. (d),y Indirect 어드레싱에서도 같은 일이 발생한다.

(d),y 모드는 (d,x)보다 훨씬 더 자주 사용된다. 후자는 Zero Page에 주소 테이블이 있음을 암시한다. Apple II 같은 컴퓨터에서는 BASIC 인터프리터가 Zero Page 대부분을 사용하므로 (d,x)가 거의 사용되지 않는다. 하지만 NES는 Zero Page에 여유 공간이 훨씬 많으며, 음악 엔진이 APU 레지스터 오프셋에 맞추어 X = 0, 4, 8, 또는 12를 사용할 수 있다.

---

## 기타 어드레싱 (Other addressing)

| 약어     | 이름                     | 설명                                                                                                                     |
| -------- | ------------------------ | ------------------------------------------------------------------------------------------------------------------------ |
| *(없음)* | 묵시적 (Implicit)        | *RTS*나 *CLC* 같은 명령어는 주소 오퍼랜드가 없으며, 결과의 도착지는 암시되어 있다.                                       |
| A        | 누산기 (Accumulator)     | 많은 명령어가 누산기에 동작할 수 있다. 예: *LSR A*. 일부 어셈블러는 해당하는 경우 오퍼랜드 없음을 암시적 *A*로 취급한다. |
| #v       | 이미디에이트 (Immediate) | 메모리 주소에서 값을 페치하는 대신, 8비트 오퍼랜드 자체를 연산의 값으로 사용한다.                                        |
| d        | Zero Page (Zero page)    | Zero Page의 8비트 주소에서 값을 페치한다.                                                                                |
| a        | Absolute (Absolute)      | 메모리 어디에서든 16비트 주소에서 값을 페치한다.                                                                         |
| label    | 상대 (Relative)          | 분기 명령어(예: *BEQ*, *BCS*)는 현재 PC에 대한 8비트 부호 있는 오프셋을 지정하는 상대 ADDRMode를 가진다.                 |
| (a)      | Indirect (Indirect)      | *JMP* 명령어는 메모리 어디에든 있는 16비트 포인터에 저장된 주소로 점프할 수 있는 특수한 간접 ADDRMode를 가진다.          |
