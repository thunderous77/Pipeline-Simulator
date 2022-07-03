//
// Created by 27595 on 2022/6/28.
//

#include "CPU.hpp"

void CPU::LUI_EX() {
    for (int j = 0; j < 12; ++j)
        EX.pass[j] = 0;
    for (int j = 12; j < 32; ++j)
        EX.pass[j] = EX.code[j];
    EX.reviseReg = true;
}

void CPU::AUIPC_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = 0;
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[j];
    int ans = ten_trans(tp) + (EX.pc << 2);
    for (int j = 0; j < 32; ++j)
        EX.pass[j] = ans >> j & 1;
    EX.reviseReg = true;
}

void CPU::JAL_EX() {
    for (int j = 0; j < 32; ++j)
        EX.pass[j] = ((EX.pc + 1) << 2) >> j & 1;
    EX.reviseReg = true;
}

void CPU::JALR_EX() {
    for (int j = 0; j < 32; ++j)
        EX.pass[j] = ((EX.pc + 1) << 2) >> j & 1;
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    bp[mp[EX.pc]].offset = (((ten_trans(tp) + ten_trans(EX.regRs1)) & ~1) >> 2) - EX.pc;
    EX.reviseReg = true;
    revise = PredictionRevise::FORWARD;
}

void CPU::BEQ_EX() {
    bool jump = (ten_trans(EX.regRs1) == ten_trans(EX.regRs2));
    if (jump) {
        if (!bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::FORWARD;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]++;
    } else {
        if (bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::BACK;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]--;
    }
}

void CPU::BNE_EX() {
    bool jump = (ten_trans(EX.regRs1) != ten_trans(EX.regRs2));
    if (jump) {
        if (!bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::FORWARD;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]++;
    } else {
        if (bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::BACK;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]--;
    }
}

void CPU::BLT_EX() {
    bool jump = (ten_trans(EX.regRs1) < ten_trans(EX.regRs2));
    if (jump) {
        if (!bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::FORWARD;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]++;
    } else {
        if (bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::BACK;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]--;
    }
}

void CPU::BGE_EX() {
    bool jump = (ten_trans(EX.regRs1) >= ten_trans(EX.regRs2));
    if (jump) {
        if (!bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::FORWARD;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]++;
    } else {
        if (bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::BACK;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]--;
    }
}

void CPU::BLTU_EX() {
    unsigned int a = tenU_trans(EX.regRs1), b = tenU_trans(EX.regRs2);
    bool jump = (a < b);
    if (jump) {
        if (!bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::FORWARD;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]++;
    } else {
        if (bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::BACK;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]--;
    }
}

void CPU::BGEU_EX() {
    unsigned int a = tenU_trans(EX.regRs1), b = tenU_trans(EX.regRs2);
    bool jump = (a >= b);
    if (jump) {
        if (!bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::FORWARD;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]++;
    } else {
        if (bp[mp[EX.pc]].BranchJump()) {
            revise = PredictionRevise::BACK;
            bp[mp[EX.pc]].wrong++;
        } else bp[mp[EX.pc]].right++;
        bp[mp[EX.pc]]--;
    }
}

void CPU::LB_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    EX.reviseReg = true;
}

void CPU::LH_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    EX.reviseReg = true;
}

void CPU::LW_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    EX.reviseReg = true;
}

void CPU::LBU_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    EX.reviseReg = true;
}

void CPU::LHU_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    EX.reviseReg = true;
}

void CPU::SB_EX() {
    int tp[32];
    for (int j = 0; j < 5; ++j)
        tp[j] = EX.code[j + 7];
    for (int j = 5; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    for (int j = 0; j < 8; ++j)
        EX.pass[j] = EX.regRs2[7 - j];
}

void CPU::SH_EX() {
    int tp[32];
    for (int j = 0; j < 5; ++j)
        tp[j] = EX.code[j + 7];
    for (int j = 5; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    for (int j = 0; j < 8; ++j)
        EX.pass[j] = EX.regRs2[7 - j];
    for (int j = 8; j < 16; ++j)
        EX.pass[j] = EX.regRs2[23 - j];
}

void CPU::SW_EX() {
    int tp[32];
    for (int j = 0; j < 5; ++j)
        tp[j] = EX.code[j + 7];
    for (int j = 5; j < 12; ++j)
        tp[j] = EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    EX.target = (ten_trans(EX.regRs1) + ten_trans(tp)) << 3;
    int mcnt = 0;
    for (int j = 0; j < 4; ++j) {
        for (int k = 7; k >= 0; --k) {
            EX.pass[mcnt] = EX.regRs2[(j << 3) + k];
            mcnt++;
        }
    }
}

void CPU::ADDI_EX() {
    int ans, tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[20 + j];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    ans = ten_trans(tp) + ten_trans(EX.regRs1);
    for (int j = 0; j < 32; ++j)
        EX.pass[j] = ans >> j & 1;
    EX.reviseReg = true;
}

void CPU::SLTI_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[20 + j];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    if (ten_trans(EX.regRs1) < ten_trans(tp))
        EX.pass[0] = 1;
    else EX.pass[0] = 0;
    for (int j = 31; j > 0; --j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::SLTIU_EX() {
    int tp[32];
    for (int j = 0; j < 12; ++j)
        tp[j] = EX.code[20 + j];
    for (int j = 12; j < 32; ++j)
        tp[j] = EX.code[31];
    if (tenU_trans(EX.regRs1) < tenU_trans(tp))
        EX.pass[0] = 1;
    else EX.pass[0] = 0;
    for (int j = 31; j > 0; --j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::XORI_EX() {
    for (int j = 0; j < 12; ++j)
        EX.pass[j] = EX.regRs1[j] ^ EX.code[j + 20];
    EX.reviseReg = true;
}

void CPU::ORI_EX() {
    for (int j = 0; j < 12; ++j)
        EX.pass[j] = EX.regRs1[j] | EX.code[j + 20];
    EX.reviseReg = true;
}

void CPU::ANDI_EX() {
    for (int j = 0; j < 12; ++j)
        EX.pass[j] = EX.regRs1[j] & EX.code[j + 20];
    for (int j = 12; j < 32; ++j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::SLLI_EX() {
    for (int j = 31; j >= EX.rs2; --j)
        EX.pass[j] = EX.regRs1[j - EX.rs2];
    for (int j = 0; j < EX.rs2; ++j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::SRLI_EX() {
    for (int j = EX.rs2; j < 32; ++j)
        EX.pass[j - EX.rs2] = EX.regRs1[j];
    for (int j = 31; j >= 32 - EX.rs2; --j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::SRAI_EX() {
    int ans = ten_trans(EX.regRs1) >> 1;
    for (int j = 0; j < 32; ++j)
        EX.pass[j] = ans >> j & 1;
    EX.reviseReg = true;
}

void CPU::ADD_EX() {
    int ans = ten_trans(EX.regRs1) + ten_trans(EX.regRs2);
    for (int i = 0; i < 32; ++i)
        EX.pass[i] = ans >> i & 1;
    EX.reviseReg = true;
}

void CPU::SLL_EX() {
    int sum_rs2 = 0;
    for (int j = 4; j >= 0; --j)
        sum_rs2 = (sum_rs2 << 1) + EX.regRs2[j];
    for (int j = 31; j >= sum_rs2; --j)
        EX.pass[j] = EX.regRs1[j - sum_rs2];
    for (int j = 0; j < sum_rs2; ++j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::SLT_EX() {
    if (ten_trans(EX.regRs1) >= ten_trans(EX.regRs2))
        EX.pass[0] = 0;
    else EX.pass[0] = 1;
    for (int j = 1; j < 32; ++j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::SLTU_EX() {
    if (tenU_trans(EX.regRs1) >= tenU_trans(EX.regRs2))
        EX.pass[0] = 0;
    else EX.pass[0] = 1;
    for (int j = 1; j < 32; ++j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::XOR_EX() {
    for (int j = 0; j < 32; j++)
        EX.pass[j] = EX.regRs1[j] ^ EX.regRs2[j];
    EX.reviseReg = true;
}

void CPU::SRL_EX() {
    int sum_rs2 = ten_trans(EX.regRs2);
    for (int j = sum_rs2; j < 32; ++j)
        EX.pass[j - sum_rs2] = EX.regRs1[j];
    for (int j = 31; j >= 32 - sum_rs2; --j)
        EX.pass[j] = 0;
    EX.reviseReg = true;
}

void CPU::OR_EX() {
    for (int j = 0; j < 32; j++)
        EX.pass[j] = EX.regRs1[j] | EX.regRs2[j];
    EX.reviseReg = true;
}

void CPU::AND_EX() {
    for (int j = 0; j < 32; j++)
        EX.pass[j] = EX.regRs1[j] & EX.regRs2[j];
    EX.reviseReg = true;
}

void CPU::SUB_EX() {
    int ans = ten_trans(EX.regRs1) - ten_trans(EX.regRs2);
    for (int j = 0; j < 32; ++j)
        EX.pass[j] = ans >> j & 1;
    EX.reviseReg = true;
}

void CPU::SRA_EX() {
    int sum_rs2 = 0;
    for (int j = 4; j >= 0; --j)
        sum_rs2 = (sum_rs2 << 1) + EX.regRs2[j];
    for (int j = sum_rs2; j < 32; ++j)
        EX.pass[j - sum_rs2] = EX.regRs1[j];
    for (int j = 30; j >= 32 - sum_rs2; --j)
        EX.pass[j] = EX.regRs1[31];
    EX.reviseReg = true;
}