// regbits: C++ templates for type-safe bit manipulation
// Copyright (C) 2019 Mark R. Rubin
//
// This file is part of regbits.
//
// The regbits program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// The regbits program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License (LICENSE.txt) along with the regbits program.  If not, see
// <https://www.gnu.org/licenses/gpl.html>


#ifndef MCU_REGBITS_HXX
#define MCU_REGBITS_HXX

#include <stdint.h>

#include <regbits.hxx>


namespace mcu {

using namespace regbits;

struct Gpio {
    static const uint32_t   NUM_BYTE_REGS = 32,
                            NUM_WORD_REGS = 32,
                            MAX_PORT_NUM  = 22;

    using  pos_t = Pos<uint32_t, Gpio>;

    struct Bytes {
        REGBITS_ARRAY_RANGE("Gpio::Bytes",
                            BYTES,
                            bytes,
                            valid,
                            uint8_t,
                            _bytes,
                            MAX_PORT_NUM);
      private:
        uint8_t _bytes[NUM_BYTE_REGS];
    };  // struct Bytes
    Bytes   bytes;
    static_assert(sizeof(Bytes) == 32, "sizeof(Bytes)");

    struct Words {
        REGBITS_ARRAY_RANGE("Gpio::Words",
                            WORDS,
                            words,
                            valid,
                            uint32_t,
                            _words,
                            MAX_PORT_NUM);
      private:
        uint32_t    _words[NUM_WORD_REGS];
    };  // struct Words
    Words   words;

    struct Set {
        using  pos_t = Pos <uint32_t, Set>;
        using bits_t = Bits<uint32_t, Set>;

        REGBITS_BITS_RANGE("Gpio::Set",
                           SET,
                           set,
                           valid,
                           uint32_t);
    };  // struct Set
    using set_t = Reg<uint32_t, Set>;
    set_t       set;

    struct Clr {
        using  pos_t = Pos <uint32_t, Clr>;
        using bits_t = Bits<uint32_t, Clr>;

        REGBITS_BITS_RANGE("Gpio::Clr",
                           CLR,
                           clr,
                           valid,
                           uint32_t);
    };  // struct Clr
    using clr_t = Reg<uint32_t, Clr>;
    clr_t       clr;
};  // struct Gpio
static_assert(sizeof(Gpio) == 168, "sizeof(Gpio)");



struct Timer {
    struct Control {
        using  pos_t = Pos <uint32_t, Control>;
        static constexpr pos_t  ENABLE_POS          = pos_t( 4),
                                CYCLE_POS           = pos_t( 5),
                                ARR_ENABLE_POS      = pos_t( 6),
                                CLOCK_SOURCE_POS    = pos_t( 7),
                                DIRECTION_POS       = pos_t(10);

        using bits_t = Bits<uint32_t, Control>;
        using mskd_t = Mskd<uint32_t, Control>;

        static constexpr bits_t ENABLE     = bits_t(1, ENABLE_POS   ),
                                CYCLE      = bits_t(1, CYCLE_POS    ),
                                ARR_ENABLE = bits_t(1, ENABLE_POS   ),
                                DIRECTION  = bits_t(1, DIRECTION_POS);

        static const uint32_t   MASK        = 0x7;

        static constexpr mskd_t
                CLOCK_SOURCE_MAIN   = mskd_t(MASK, 0, CLOCK_SOURCE_POS),
                CLOCK_SOURCE_PLL    = mskd_t(MASK, 1, CLOCK_SOURCE_POS),
                CLOCK_SOURCE_EXTERN = mskd_t(MASK, 2, CLOCK_SOURCE_POS),
                CLOCK_SOURCE_WWV    = mskd_t(MASK, 3, CLOCK_SOURCE_POS),
                CLOCK_SOURCE_GPS    = mskd_t(MASK, 4, CLOCK_SOURCE_POS),
                CLOCK_SOURCE_CESIUM = mskd_t(MASK, 5, CLOCK_SOURCE_POS);
    };  // struct Control
    using control_t = Reg<uint32_t, Control>;
    control_t       control;

    struct Prescale {
        using  pos_t = Pos <uint32_t, Prescale>;
        using mskd_t = Mskd<uint32_t, Prescale>;

        static constexpr pos_t  PRESCALER_POS = pos_t(24);

        static constexpr uint32_t   MAX_PRESCALER_VAL = 0xff;
        static const     uint32_t   PRESCALER_MASK    = 0xff;

        REGBITS_MSKD_RANGE("Timer::Prescale",
                           PRESCALER,
                           prescaler,
                           valid,
                           PRESCALER_MASK,
                           PRESCALER_POS,
                           MAX_PRESCALER_VAL);
    };  // struct Prescale
    using prescale_t = Reg<uint32_t, Prescale>;
    prescale_t      prescale;

    struct Autoreload {
        using  pos_t = Pos <uint32_t, Autoreload>;
        using mskd_t = Mskd<uint32_t, Autoreload>;

        static constexpr pos_t  AUTORELOADER_POS = pos_t(0);

        static constexpr uint32_t   MAX_AUTORELOAD_VAL = 0x00ffffff;
        static const     uint32_t   AUTORELOAD_MASK    = 0x00ffffff;

        REGBITS_MSKD_RANGE("Timer::Prescale",
                           AUTORELOADER,
                           autoreloader,
                           valid,
                           AUTORELOAD_MASK,
                           AUTORELOADER_POS,
                           MAX_AUTORELOAD_VAL);
    };  // struct Autoreload
    using autoreload_t = Reg<uint32_t, Autoreload>;
    autoreload_t    autoreload;

    struct Interrupts {
        using  pos_t = Pos <uint32_t, Interrupts>;

        static constexpr pos_t  TIMEOUT_POS         = pos_t(  8),
                                UNDERFLOW_POS       = pos_t(  9);

        using bits_t = Bits<uint32_t, Interrupts>;

        static constexpr bits_t TIMEOUT         = bits_t(1, TIMEOUT_POS)  ,
                                UNDERFLOW       = bits_t(1, UNDERFLOW_POS);
    };  // struct Interrupts
    using interrupts_t = Reg<uint32_t, Interrupts>;
    interrupts_t    interrupts;

    struct Status {
        using  pos_t = Pos <uint32_t, Status>;

        static constexpr pos_t  TIMEOUT_POS     = pos_t( 16),
                                UNDERFLOW_POS   = pos_t( 17);

        using bits_t = Bits<uint32_t, Status>;

        static constexpr bits_t TIMEOUT         = bits_t(1, TIMEOUT_POS),
                                UNDERFLOW       = bits_t(1, UNDERFLOW_POS);
    };  // struct Status
    using status_t = Reg<uint32_t, Status>;
    status_t    status;

    struct Counter {
        using  pos_t = Pos <uint32_t, Counter>;

        static constexpr pos_t  COUNT_POS = pos_t(   8);

        using bits_t = Bits<uint32_t, Counter>;

        static constexpr bits_t COUNT = bits_t(1, COUNT_POS);
    };  // struct Counter
    using counter_t = Reg<uint32_t, Counter>;
    counter_t   counter;

}; // struct Timer;
static_assert(sizeof(Timer) == 24, "sizeof(Timer)");



struct Serial {
    struct Control {
        using  pos_t = Pos <uint32_t, Control>;

        static constexpr pos_t  ENABLE_POS      = pos_t(    0),
                                RECV_POS        = pos_t(    1),
                                XMIT_POS        = pos_t(    2);

        using bits_t = Bits<uint32_t, Control>;
        using mskd_t = Mskd<uint32_t, Control>;

        static constexpr bits_t ENABLE      = bits_t(1, ENABLE_POS),
                                RECV        = bits_t(1, RECV_POS)  ,
                                XMIT        = bits_t(1, XMIT_POS)  ;
    };  // struct Control
    using control_t = Reg<uint32_t, Control>;
    control_t   control;

    struct Config {
        using  pos_t = Pos <uint32_t, Config>;

        static constexpr pos_t  MODE_POS        = pos_t( 0),
                                DATALEN_POS     = pos_t( 1),
                                PARITY_POS      = pos_t( 3),
                                ENDIAN_POS      = pos_t( 5),
                                POLARITY_POS    = pos_t( 6),
                                RXPORT_POS      = pos_t( 7),
                                TXPORT_POS      = pos_t(12);

        static const uint32_t   DATALEN_MASK    = 0x03,
                                PARITY_MASK     = 0x03,
                                RXPORT_MASK     = 0x1f,
                                TXPORT_MASK     = 0x1f;

        using bits_t = Bits<uint32_t, Config>;
        using mskd_t = Mskd<uint32_t, Config>;

        static constexpr bits_t MODE        = bits_t(1, MODE_POS    ),
                                ENDIAN      = bits_t(1, ENDIAN_POS  ),
                                POLARITY    = bits_t(1, POLARITY_POS);

        static constexpr mskd_t
                DATALEN_8_BITS  = mskd_t(DATALEN_MASK, 0, DATALEN_POS),
                DATALEN_16_BITS = mskd_t(DATALEN_MASK, 1, DATALEN_POS),
                DATALEN_32_BITS = mskd_t(DATALEN_MASK, 2, DATALEN_POS),
                PARITY_ODD      = mskd_t(PARITY_MASK,  0, PARITY_POS ),
                PARITY_EVEN     = mskd_t(PARITY_MASK,  1, PARITY_POS ),
                PARITY_CRC      = mskd_t(PARITY_MASK,  2, PARITY_POS );

        static constexpr uint32_t   MAX_PORT_NUM = 31;

        REGBITS_MSKD_RANGE("Serial::Config",
                           RXPORT,
                           rxport,
                           valid_rxport,
                           RXPORT_MASK,
                           RXPORT_POS,
                           MAX_PORT_NUM);

        REGBITS_MSKD_RANGE("Serial::Config",
                           TXPORT,
                           txport,
                           valid_txport,
                           TXPORT_MASK,
                           TXPORT_POS,
                           MAX_PORT_NUM);
    };  // struct Config
    using config_t = Reg<uint32_t, Config>;
    config_t    config;

    struct Interrupts {
        using  pos_t = Pos <uint32_t, Interrupts>;

        static constexpr pos_t  RXREADY_POS     = pos_t( 13),
                                TXREADY_POS     = pos_t( 14),
                                RXOVERFLOW_POS  = pos_t( 15),
                                TXUNDERFLOW_POS = pos_t( 16);

        using bits_t = Bits<uint32_t, Interrupts>;

        static constexpr bits_t RXREADY     = bits_t(1, RXREADY_POS)    ,
                                TXREADY     = bits_t(1, TXREADY_POS)    ,
                                RXOVERFLOW  = bits_t(1, RXOVERFLOW_POS) ,
                                TXUNDERFLOW = bits_t(1, TXUNDERFLOW_POS);
    };  // struct Interrupts
    using interrupts_t = Reg<uint32_t, Interrupts>;
    interrupts_t    interrupts;

    struct Status {
        using  pos_t = Pos <uint32_t, Status>;

        static constexpr pos_t  RXREADY_POS     = pos_t(  3),
                                TXREADY_POS     = pos_t(  4),
                                RXOVERFLOW_POS  = pos_t(  5),
                                TXUNDERFLOW_POS = pos_t(  6);

        using bits_t = Bits<uint32_t, Status>;

        static constexpr bits_t RXREADY     = bits_t(1, RXREADY_POS)    ,
                                TXREADY     = bits_t(1, TXREADY_POS)    ,
                                RXOVERFLOW  = bits_t(1, RXOVERFLOW_POS) ,
                                TXUNDERFLOW = bits_t(1, TXUNDERFLOW_POS);
    };  // struct Status
    using status_t = Reg<uint32_t, Status>;
    status_t    status;

    struct Rxbuffer {
        using  pos_t = Pos <uint32_t, Rxbuffer>;

        static constexpr pos_t  DATA_POS = pos_t(   0);
        using bits_t = Bits<uint32_t, Rxbuffer>;

        static constexpr bits_t DATA = bits_t(1, DATA_POS);
    };  // struct Rxbuffer
    using rxbuffer_t = Reg<uint32_t, Rxbuffer>;
    rxbuffer_t rxbuffer;

    struct Txbuffer {
        using  pos_t = Pos <uint32_t, Txbuffer>;

        static constexpr pos_t  DATA_POS = pos_t(0);

        using bits_t = Bits<uint32_t, Txbuffer>;

        static constexpr bits_t DATA = bits_t(1, DATA_POS);
    };  // struct Txbuffer
    using txbuffer_t = Reg<uint32_t, Txbuffer>;
    txbuffer_t txbuffer;

};  // struct Serial
static_assert(sizeof(Serial) == 24, "sizeof(Serial)");



#ifndef PERIPH_BASE
#error Must define PERIPH_BASE via -DPERIPH_BASE=xxxx on commandline
#endif

#define GPIO_BASE       ((PERIPH_BASE) + 0x00000000)
#define TIMER_BASE      ((PERIPH_BASE) + 0x00000200)
#define SERIAL_BASE     ((PERIPH_BASE) + 0x00000280)

#define GPIO0_BASE      ((GPIO_BASE)   + 0x00000000)
#define GPIO1_BASE      ((GPIO_BASE)   + 0x00000100)

#define TIMER0_BASE     ((TIMER_BASE)  + 0x00000000)
#define TIMER1_BASE     ((TIMER_BASE)  + 0x00000020)
#define TIMER2_BASE     ((TIMER_BASE)  + 0x00000040)
#define TIMER3_BASE     ((TIMER_BASE)  + 0x00000060)

#define SERIAL0_BASE    ((SERIAL_BASE) + 0x00000000)
#define SERIAL1_BASE    ((SERIAL_BASE) + 0x00000020)
#define SERIAL2_BASE    ((SERIAL_BASE) + 0x00000040)

static Gpio* const      gpio0  = reinterpret_cast<Gpio*>(GPIO0_BASE);
static Gpio* const      gpio1  = reinterpret_cast<Gpio*>(GPIO1_BASE);

static Timer* const     timer0 = reinterpret_cast<Timer*>(TIMER0_BASE);
static Timer* const     timer1 = reinterpret_cast<Timer*>(TIMER1_BASE);
static Timer* const     timer2 = reinterpret_cast<Timer*>(TIMER2_BASE);
static Timer* const     timer3 = reinterpret_cast<Timer*>(TIMER3_BASE);

static Serial* const    serial0 = reinterpret_cast<Serial*>(SERIAL0_BASE);
static Serial* const    serial1 = reinterpret_cast<Serial*>(SERIAL1_BASE);
static Serial* const    serial2 = reinterpret_cast<Serial*>(SERIAL2_BASE);

}  // namespace mcu

#endif // #ifdef MCU_REGBITS_HXX
