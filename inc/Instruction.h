/*!
   \file Instruction.h
   \brief Decode instructions part of the RISC-V
   \author Màrius Montón
   \date August 2018
*/

#ifndef INSTRUCTION__H
#define INSTRUCTION__H

#include "systemc"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

typedef enum {
OP_LUI,
OP_AUIPC,
OP_JAL,
OP_JALR,

OP_BEQ,
OP_BNE,
OP_BLT,
OP_BGE,
OP_BLTU,
OP_BGEU,

OP_LB,
OP_LH,
OP_LW,
OP_LBU,
OP_LHU,

OP_SB,
OP_SH,
OP_SW,

OP_ADDI,
OP_SLTI,
OP_SLTIU,
OP_XORI,
OP_ORI,
OP_ANDI,
OP_SLLI,
OP_SRLI,
OP_SRAI,

OP_ADD,
OP_SUB,
OP_SLL,
OP_SLT,
OP_SLTU,
OP_XOR,
OP_SRL,
OP_SRA,
OP_OR,
OP_AND,

OP_ERROR
} opCodes;


typedef enum {
  LUI     = 0b0110111,
  AUIPC   = 0b0010111,
  JAL     = 0b1101111,
  JALR    = 0b1100111,

  BEQ     = 0b1100011,
  BEQ_F   = 0b000,
  BNE_F   = 0b001,
  BLT_F   = 0b100,
  BGE_F   = 0b101,
  BLTU_F  = 0b110,
  BGEU_F  = 0b111,

  LB      = 0b0000011,
  LB_F    = 0b000,
  LH_F    = 0b001,
  LW_F    = 0b010,
  LBU_F   = 0b100,
  LHU_F   = 0b101,

  SB      = 0b0100011,
  SB_F    = 0b000,
  SH_F    = 0b001,
  SW_F    = 0b010,

  ADDI    = 0b0010011,
  ADDI_F  = 0b000,
  SLTI_F  = 0b010,
  SLTIU_F = 0b011,
  XORI_F  = 0b100,
  ORI_F   = 0b110,
  ANDI_F  = 0b111,
  SLLI_F  = 0b001,
  SRLI_F  = 0b101,
  SRLI_F7 = 0b0000000,
  SRAI_F7 = 0b0100000,

  ADD     = 0b0110011,
  ADD_F   = 0b000,
  SUB_F   = 0b000,
  ADD_F7  = 0b0000000,
  SUB_F7  = 0b0100000,

  SLL_F   = 0b001,
  SLT_F   = 0b010,
  SLTU_F  = 0b011,
  XOR_F   = 0b100,
  SRL_F   = 0b101,
  SRA_F   = 0b101,
  SRL_F7  = 0b0000000,
  SRA_F7  = 0b0100000,
  OR_F    = 0b110,
  AND_F   = 0b111,
} Codes;

/**
 * @brief Instruction decoding and fields access
 */
class Instruction{
public:

  /**
   * @brief Constructor
   * @param instr Instruction to decode
   */
  Instruction(sc_int<32> instr);

  /**
   * @brief Access to opcode field
   * @return return opcode field
   */
  inline int32_t opcode() {
    // cout << "OP: " << m_instr << endl;
    return m_instr.range(6,0);
  }

  /**
   * @brief Access to rd field
   * @return rd field
   */
  inline int32_t rd() {
    return m_instr.range(11, 7);
  }

  /**
   * @brief Access to funct3 field
   * @return funct3 field
   */
  inline int32_t funct3() {
    return m_instr.range(14, 12);
  }

  /**
   * @brief Access to rs1 field
   * @return rs1 field
   */
  inline int32_t rs1() {
    return m_instr.range(19, 15);
  }

  /**
   * @brief Access to rs2 field
   * @return rs2 field
   */
  inline int32_t rs2() {
    return m_instr.range(24, 20);
  }

  /**
   * @brief Access to funct7 field
   * @return funct7 field
   */
  inline int32_t funct7() {
    return m_instr.range(31, 25);
  }

  /**
   * @brief Access to immediate field for I-type
   * @return immediate_I field
   */
  inline int32_t imm_I() {
    int32_t aux = 0;

    aux = m_instr.range(31, 20);

    /* sign extension (optimize) */
    if (m_instr[31] == 1) {
      aux |= (0b11111111111111111111) << 12;
    }

    return aux;
  }

  /**
   * @brief Access to immediate field for S-type
   * @return immediate_S field
   */
  inline int32_t imm_S() {
    int32_t aux = 0;

    aux  = m_instr.range(31, 25) << 5;
    aux |= m_instr.range(11,7);

    if (m_instr[31] == 1) {
      aux |= (0b11111111111111111111) << 12;
    }

    return aux;
  }

  /**
   * @brief Access to immediate field for U-type
   * @return immediate_U field
   */
  inline int32_t imm_U() {
    return m_instr.range(31, 12);
  }

  /**
   * @brief Access to immediate field for B-type
   * @return immediate_B field
   */
  inline int32_t imm_B() {
    int32_t aux = 0;

    aux |= m_instr[7] << 11;
    aux |= m_instr.range(30, 25) << 5;
    aux |= m_instr[31] << 12;
    aux |= m_instr.range(11, 8) << 1;

    if (m_instr[31] == 1) {
      aux |= (0b11111111111111111111) << 12;
    }

    return aux;
  }

  /**
   * @brief Access to immediate field for J-type
   * @return immediate_J field
   */
  inline int32_t imm_J() {
    int32_t aux = 0;

    aux = m_instr[31] << 20;
    aux |= m_instr.range(19,12) << 12;
    aux |= m_instr[20] << 11;
    aux |= m_instr.range(30,21) << 1;

    /* bit extension (better way to do that?) */
    if (m_instr[31] == 1) {
      aux |= (0b111111111111) << 20;
    }
    return aux;
  }

  inline int32_t csr() {
    return imm_I();
  }

  /**
   * @brief Decodes opcode of instruction
   * @return opcode of instruction
   */
  opCodes decode();

  inline void dump() {
    cout << hex << "0x" << m_instr << dec << endl;
  }
private:
  sc_int<32> m_instr;
};

#endif
