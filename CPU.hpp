//
// Created by 27595 on 2022/6/28.
//

#ifndef PIPELINE_SIMULATOR_CPU_HPP
#define PIPELINE_SIMULATOR_CPU_HPP

#include <bits/stdc++.h>
//#include "Execute.hpp"

using namespace std;
enum Itype {
    LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI,
    ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND
};

class CPU {
private:
    int Register[100][32], Memory[10000000], pc = 0, clock = 0, offset;
    bool jump;//jump表示条件判断跳转语句是否执行

    class tmpReg {
    public:
        int rs1, rs2, rd, target, pc;
        int code[32], regRs1[32], regRs2[32], regRd[32], pass[32];
        Itype type;
        bool reviseReg, useful = false;//reviseReg表示是否修改Register[rd],useful表示是否执行

        tmpReg &operator=(const tmpReg &other) {
            if (this == &other) return *this;
            rs1 = other.rs1;
            rs2 = other.rs2;
            rd = other.rd;
            reviseReg = other.reviseReg;
            useful = other.useful;
            target = other.target;
            pc = other.pc;
            for (int i = 0; i < 32; ++i) {
                code[i] = other.code[i];
                regRs1[i] = other.regRs1[i];
                regRs2[i] = other.regRs2[i];
                regRd[i] = other.regRd[i];
                pass[i] = other.pass[i];
            }
            type = other.type;
            return *this;
        }
    };

    tmpReg IF, ID, EX, MEM, WB;

    bool Exit(int *code) {
        int tmp = 0;
        for (int i = 31; i >= 0; --i)
            tmp = (tmp << 1) + code[i];
        return tmp == 267388179;
    }

    bool rs1Use() {
        return (!(ID.type == LUI || ID.type == AUIPC || ID.type == JAL));
    }

    bool rs2Use() {
        return (ID.type == BEQ || ID.type == BNE || ID.type == BLT || ID.type == BGE ||
                ID.type == BLTU || ID.type == BGEU || ID.type == SB ||
                ID.type == SH || ID.type == SW || ID.type == ADD || ID.type == SUB || ID.type == SLL ||
                ID.type == SLT || ID.type == SLTU ||
                ID.type == XOR || ID.type == SRL || ID.type == SRA || ID.type == OR || ID.type == AND);
    }

    bool IsLoad(tmpReg tmp) {
        return (tmp.type == LB || tmp.type == LH || tmp.type == LW || tmp.type == LBU || tmp.type == LHU);
    }

    int ten_trans(int *a) {
        int tmp = 0;
        if (a[31] == 0) {
            for (int i = 31; i >= 0; --i)
                tmp = (tmp << 1) + a[i];
        } else {
            for (int i = 31; i >= 0; --i)
                tmp = (tmp << 1) + 1 - a[i];
            tmp = -1 - tmp;
        }
        return tmp;
    }

    int tenU_trans(int *a) {
        int tmp = 0;
        for (int i = 31; i >= 0; --i)
            tmp = (tmp << 1) + a[i];
        return tmp;
    }

    bool MemAccess() {
        return (EX.type == LB || EX.type == LH || EX.type == LW || EX.type == LBU
                || EX.type == LHU || EX.type == SB || EX.type == SH || EX.type == SW);
    }

    void LUI_EX();

    void AUIPC_EX();

    void JAL_EX();

    void JALR_EX();

    void BEQ_EX();

    void BNE_EX();

    void BLT_EX();

    void BGE_EX();

    void BLTU_EX();

    void BGEU_EX();

    void LB_EX();

    void LH_EX();

    void LW_EX();

    void LBU_EX();

    void LHU_EX();

    void SB_EX();

    void SH_EX();

    void SW_EX();

    void ADDI_EX();

    void SLTI_EX();

    void SLTIU_EX();

    void XORI_EX();

    void ORI_EX();

    void ANDI_EX();

    void SLLI_EX();

    void SRLI_EX();

    void SRAI_EX();

    void ADD_EX();

    void SLL_EX();

    void SLT_EX();

    void SLTU_EX();

    void XOR_EX();

    void SRL_EX();

    void OR_EX();

    void AND_EX();

    void SUB_EX();

    void SRA_EX();

public:
    CPU() = default;

    void codeStore() {
        string in, Finstruction, Sinstruction[1000];
        int Scnt;
        while (cin >> in) {
            if (in[0] == '@') {
                if (Scnt != 0) {
                    //转成32位数组
                    int sum = Scnt / 4, tmp, start = 0, mcnt = 0;
                    int tmpcode[32];
                    for (int i = 0; i < Finstruction.length(); ++i) {
                        if (isdigit(Finstruction[i]))
                            start = (start << 4) + int(Finstruction[i] - '0');
                        else start = (start << 4) + 10 + int(Finstruction[i] - 'A');
                    }
                    for (int i = 0; i < sum; ++i) {
                        for (int j = 0; j < Sinstruction[i].length(); ++j) {
                            if (isdigit(Sinstruction[i][j]))
                                tmp = int(Sinstruction[i][j] - '0');
                            else tmp = 10 + int(Sinstruction[i][j] - 'A');
                            for (int k = 0; k < 4; ++k)
                                tmpcode[4 * j + 3 - k] = (tmp >> k) & 1;
                        }
                        for (int j = 0; j < 32; ++j) {
                            Memory[mcnt + (start << 3)] = tmpcode[j];
                            mcnt++;
                        }
                    }
                }
                Scnt = 0;
                Finstruction = "";
                for (int i = 1; i < in.length(); ++i)
                    Finstruction += in[i];
            } else {
                if (Scnt % 4 == 0) Sinstruction[Scnt / 4] = "";
                Sinstruction[Scnt / 4] += in;
                Scnt++;
            }
        }
        //转成32位数组
        int sum = Scnt / 4, tmp, start = 0, mcnt = 0;
        int tmpcode[32];
        for (int i = 0; i < Finstruction.length(); ++i) {
            if (isdigit(Finstruction[i]))
                start = (start << 4) + int(Finstruction[i] - '0');
            else start = (start << 4) + 10 + int(Finstruction[i] - 'A');
        }
        for (int i = 0; i < sum; ++i) {
            for (int j = 0; j < Sinstruction[i].length(); ++j) {
                if (isdigit(Sinstruction[i][j]))
                    tmp = int(Sinstruction[i][j] - '0');
                else tmp = 10 + int(Sinstruction[i][j] - 'A');
                for (int k = 0; k < 4; ++k)
                    tmpcode[4 * j + 3 - k] = (tmp >> k) & 1;
            }
            for (int j = 0; j < 32; ++j) {
                Memory[mcnt + (start << 3)] = tmpcode[j];
                mcnt++;
            }
        }
    }

    void InstructionFetch() {
        IF.useful = true;
        IF.pc = pc;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j)
                IF.code[(i << 3) + j] = Memory[(pc << 5) + (i << 3) + 7 - j];
        }
        pc++;
    }

    void InstructionDecode() {
        if (!ID.useful) return;
        ID.rd = ID.rs1 = ID.rs2 = 0;
        for (int j = 0; j < 5; ++j)
            ID.rd += ID.code[j + 7] << j;
        for (int j = 0; j < 5; ++j)
            ID.rs1 += ID.code[15 + j] << j;
        for (int j = 0; j < 5; ++j)
            ID.rs2 += ID.code[20 + j] << j;
        for (int i = 0; i < 32; ++i) {
            ID.regRs1[i] = Register[ID.rs1][i];
            ID.regRs2[i] = Register[ID.rs2][i];
            ID.regRd[i] = Register[ID.rd][i];
        }
        if (ID.code[6] == 0 && ID.code[5] == 1 && ID.code[4] == 1 && ID.code[3] == 0 &&
            ID.code[2] == 1) //LUI
            ID.type = LUI;
        else if (ID.code[6] == 0 && ID.code[5] == 0 && ID.code[4] == 1 && ID.code[3] == 0 &&
                 ID.code[2] == 1) //AUIPC
            ID.type = AUIPC;
        else if (ID.code[6] == 1 && ID.code[5] == 1 && ID.code[4] == 0 && ID.code[3] == 1 &&
                 ID.code[2] == 1) //JAL
            ID.type = JAL;
        else if (ID.code[6] == 1 && ID.code[5] == 1 && ID.code[4] == 0 && ID.code[3] == 0 &&
                 ID.code[2] == 1) //JALR
            ID.type = JALR;
        else if (ID.code[6] == 1 && ID.code[5] == 1 && ID.code[4] == 0 && ID.code[3] == 0 &&
                 ID.code[2] == 0) {
            if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 0) //BEQ
                ID.type = BEQ;
            else if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 1) //BNE
                ID.type = BNE;
            else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 0) //BLT
                ID.type = BLT;
            else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 1) //BGE
                ID.type = BGE;
            else if (ID.code[14] == 1 && ID.code[13] == 1 && ID.code[12] == 0) //BLTU
                ID.type = BLTU;
            else if (ID.code[14] == 1 && ID.code[13] == 1 && ID.code[12] == 1) //BGEU
                ID.type = BGEU;
        } else if (ID.code[6] == 0 && ID.code[5] == 0 && ID.code[4] == 0 && ID.code[3] == 0 &&
                   ID.code[2] == 0) {
            if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 0) //LB
                ID.type = LB;
            else if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 1) //LH
                ID.type = LH;
            else if (ID.code[14] == 0 && ID.code[13] == 1 && ID.code[12] == 0) //LW
                ID.type = LW;
            else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 0) //LBU
                ID.type = LBU;
            else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 1) //LHU
                ID.type = LHU;
        } else if (ID.code[6] == 0 && ID.code[5] == 1 && ID.code[4] == 0 && ID.code[3] == 0 &&
                   ID.code[2] == 0) {
            if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 0) //SB
                ID.type = SB;
            else if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 1) //SH
                ID.type = SH;
            else if (ID.code[14] == 0 && ID.code[13] == 1 && ID.code[12] == 0) //SW
                ID.type = SW;
        } else if (ID.code[6] == 0 && ID.code[5] == 0 && ID.code[4] == 1 && ID.code[3] == 0 &&
                   ID.code[2] == 0) {
            if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 0) //ADDI
                ID.type = ADDI;
            else if (ID.code[14] == 0 && ID.code[13] == 1 && ID.code[12] == 0) //SLTI
                ID.type = SLTI;
            else if (ID.code[14] == 0 && ID.code[13] == 1 && ID.code[12] == 1) //SLTIU
                ID.type = SLTIU;
            else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 0) //XORI
                ID.type = XORI;
            else if (ID.code[14] == 1 && ID.code[13] == 1 && ID.code[12] == 0) //ORI
                ID.type = ORI;
            else if (ID.code[14] == 1 && ID.code[13] == 1 && ID.code[12] == 1) //ANDI
                ID.type = ANDI;
            else if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 1) //SLLI
                ID.type = SLLI;
            else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 1) {
                if (ID.code[31] == 0 && ID.code[30] == 0) //SRLI
                    ID.type = SRLI;
                else if (ID.code[31] == 0 && ID.code[30] == 1) //SRAI
                    ID.type = SRAI;
            }
        } else if (ID.code[6] == 0 && ID.code[5] == 1 && ID.code[4] == 1 && ID.code[3] == 0 &&
                   ID.code[2] == 0) {
            if (ID.code[31] == 0 && ID.code[30] == 0) {
                if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 0) //ADD
                    ID.type = ADD;
                else if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 1) //SLL
                    ID.type = SLL;
                else if (ID.code[14] == 0 && ID.code[13] == 1 && ID.code[12] == 0) //SLT
                    ID.type = SLT;
                else if (ID.code[14] == 0 && ID.code[13] == 1 && ID.code[12] == 1) //SLTU
                    ID.type = SLTU;
                else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 0) //XOR
                    ID.type = XOR;
                else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 1) //SRL
                    ID.type = SRL;
                else if (ID.code[14] == 1 && ID.code[13] == 1 && ID.code[12] == 0) //OR
                    ID.type = OR;
                else if (ID.code[14] == 1 && ID.code[13] == 1 && ID.code[12] == 1) //AND
                    ID.type = AND;
            } else if (ID.code[31] == 0 && ID.code[30] == 1) {
                if (ID.code[14] == 0 && ID.code[13] == 0 && ID.code[12] == 0)//SUB
                    ID.type = SUB;
                else if (ID.code[14] == 1 && ID.code[13] == 0 && ID.code[12] == 1) //SRA
                    ID.type = SRA;
            }
        }
    }

    void Execute() {
        if (!EX.useful) return;
        offset = 0;
        jump = false;
        EX.reviseReg = false;
        switch (EX.type) {
            case LUI:
                LUI_EX();
                break;
            case AUIPC:
                AUIPC_EX();
                break;
            case JAL:
                JAL_EX();
                break;
            case JALR:
                JALR_EX();
                break;
            case BEQ:
                BEQ_EX();
                break;
            case BNE:
                BNE_EX();
                break;
            case BLT:
                BLT_EX();
                break;
            case BGE:
                BGE_EX();
                break;
            case BLTU:
                BLTU_EX();
                break;
            case BGEU:
                BGEU_EX();
                break;
            case LB:
                LB_EX();
                break;
            case LH:
                LH_EX();
                break;
            case LW:
                LW_EX();
                break;
            case LBU:
                LBU_EX();
                break;
            case LHU:
                LHU_EX();
                break;
            case SB:
                SB_EX();
                break;
            case SH:
                SH_EX();
                break;
            case SW:
                SW_EX();
                break;
            case ADDI:
                ADDI_EX();
                break;
            case SLTI:
                SLTI_EX();
                break;
            case SLTIU:
                SLTIU_EX();
                break;
            case XORI:
                XORI_EX();
                break;
            case ORI:
                ORI_EX();
                break;
            case ANDI:
                ANDI_EX();
                break;
            case SLLI:
                SLLI_EX();
                break;
            case SRLI:
                SRLI_EX();
                break;
            case SRAI:
                SRAI_EX();
                break;
            case ADD:
                ADD_EX();
                break;
            case SLL:
                SLL_EX();
                break;
            case SLT:
                SLT_EX();
                break;
            case SLTU:
                SLTU_EX();
                break;
            case XOR:
                XOR_EX();
                break;
            case SRL:
                SRL_EX();
                break;
            case OR:
                OR_EX();
                break;
            case AND:
                AND_EX();
                break;
            case SUB:
                SUB_EX();
                break;
            case SRA:
                SRA_EX();
                break;
        }
    }

    int DataForwarding() {//>0:stall3个周期（MemoryAccess）
        if (MEM.reviseReg) {//Memoryaccess已完成
            if (MEM.rd == ID.rs1 && rs1Use() && ID.rs1 != 0) {
                for (int i = 0; i < 32; ++i)
                    ID.regRs1[i] = MEM.pass[i];
            } else if (MEM.rd == ID.rs2 && rs2Use() && ID.rs2 != 0) {
                for (int i = 0; i < 32; ++i)
                    ID.regRs2[i] = MEM.pass[i];
            }
        }
        if (EX.reviseReg) {//Execute已完成
            if (EX.rd == ID.rs1 && rs1Use() && ID.rs1 != 0) {//1
                if (IsLoad(EX)) {
                    return 1;
                } else {
                    for (int i = 0; i < 32; ++i)
                        ID.regRs1[i] = EX.pass[i];
                }
            } else if (EX.rd == ID.rs2 && rs2Use() && ID.rs2 != 0) {//2
                if (IsLoad(EX)) {
                    return 2;
                } else {
                    for (int i = 0; i < 32; ++i)
                        ID.regRs2[i] = EX.pass[i];
                }
            }
        }
        WB = MEM;
        MEM = EX;
        EX = ID;
        ID = IF;
        return 0;
    }

    void MemoryAccess() {
        if (!MEM.useful) return;
        int mcnt;
        switch (MEM.type) {
            case LB:
                for (int j = 0; j < 8; ++j)
                    MEM.pass[7 - j] = Memory[MEM.target + j];
                for (int j = 8; j < 32; ++j)
                    MEM.pass[j] = MEM.pass[7];
                break;
            case LH:
                for (int j = 0; j < 8; ++j)
                    MEM.pass[7 - j] = Memory[MEM.target + j];
                for (int j = 8; j < 16; ++j)
                    MEM.pass[23 - j] = Memory[MEM.target + j];
                for (int j = 16; j < 32; ++j)
                    MEM.pass[j] = MEM.pass[15];
                break;
            case LW:
                mcnt = 0;
                for (int j = 0; j < 4; ++j) {
                    for (int k = 7; k >= 0; --k) {
                        MEM.pass[(j << 3) + k] = Memory[MEM.target + mcnt];
                        mcnt++;
                    }
                }
                break;
            case LBU:
                for (int j = 0; j < 8; ++j)
                    MEM.pass[7 - j] = Memory[MEM.target + j];
                for (int j = 8; j < 32; ++j)
                    MEM.pass[j] = 0;
                break;
            case LHU:
                for (int j = 0; j < 8; ++j)
                    MEM.pass[7 - j] = Memory[MEM.target + j];
                for (int j = 8; j < 16; ++j)
                    MEM.pass[23 - j] = Memory[MEM.target + j];
                for (int j = 16; j < 32; ++j)
                    MEM.pass[j] = 0;
                break;
            case SB:
                for (int j = 0; j < 8; ++j)
                    Memory[MEM.target + j] = MEM.pass[j];
                break;
            case SH:
                for (int j = 0; j < 16; ++j)
                    Memory[MEM.target + j] = MEM.pass[j];
                break;
            case SW:
                for (int j = 0; j < 32; ++j)
                    Memory[MEM.target + j] = MEM.pass[j];
                break;
        }
    }

    void WriteBack() {
        if (!WB.useful) return;
        if (WB.reviseReg && WB.rd != 0) {
            for (int i = 0; i < 32; ++i)
                Register[WB.rd][i] = WB.pass[i];
        }
    }


    void run() {
        int forward;
        while (!Exit(MEM.code)) {
//            if (WB.useful) {
//                printf("%04X", WB.pc << 2);
//                cout << endl;
//            }
//            cout << "clock: " << clock << "\n";
            clock++;
            forward = DataForwarding();
            if (forward > 0) {//stall
                clock += 3;
                WB = MEM;
                WriteBack();
                MEM = EX;
                MemoryAccess();
                if (forward == 1) {
                    for (int i = 0; i < 32; ++i)
                        ID.regRs1[i] = MEM.pass[i];
                } else {
                    for (int i = 0; i < 32; ++i)
                        ID.regRs2[i] = MEM.pass[i];
                }
                EX = ID;
                ID = IF;
                Execute();
                if (jump) {
                    pc = pc - 2 + offset;
                    InstructionFetch();
                    clock++;
                    ID = IF;
                }
                InstructionDecode();
                InstructionFetch();
            } else {
                if (MemAccess())//MemoryAccess模拟3个周期
                    clock += 2;
                WriteBack();
                MemoryAccess();
                Execute();
                if (jump) {
                    pc = pc - 2 + offset;
                    InstructionFetch();
                    clock++;
                    ID = IF;
                }
                InstructionDecode();
                InstructionFetch();
            }
//            for (int j = 0; j < 32; ++j) {
//                cout << "reg[" << j << "]=" << ten_trans(Register[j]) << "  ";
//                if (j % 8 == 7) cout << "\n";
//            }
        }
        int tmp = tenU_trans(Register[10]) & 255u;
        cout << tmp << "\n";
    }
};


#endif //PIPELINE_SIMULATOR_CPU_HPP
