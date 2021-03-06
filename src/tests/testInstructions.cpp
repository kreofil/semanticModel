#include <iostream>
//#include <fstream>
//#include <sstream>

//using namespace std;

#include "ilist.h"
#include "creator.h"

void testInstructions() {
    std::cout << "Semantic model Instruction List test\n";
    std::cout << "===================\n\n";

    Module module;      // Формирование тестовой единицы компиляции
    //Creator creator;
    module.setModuleName("InstructionTest");
    NameTable* nt = module.getLocalNameTable();

    // Создание целочисленной переменной
    // Поиск артефакта в общем пространстве имен
    Artefact* aTmp = nt->globalFind("INTEGER");
    TypeContext* tc = dynamic_cast<TypeContext*>(aTmp->getContext());
    if(tc != nullptr) {
        VarContext* vContext = Creator::CreateVarContext(tc);
        module.addArtefact("intVar01", vContext, true);
    }

    // Создание второй (закрытой) целочисленной переменной
    // Поиск артефакта в общем пространстве имен
    aTmp = nt->globalFind("INTEGER");
    tc = dynamic_cast<TypeContext*>(aTmp->getContext());
    if(tc != nullptr) {
        VarContext* vContext = Creator::CreateVarContext(tc);
        module.addArtefact("intVar02", vContext, false);
    }

    // Создание булевской переменной
    // Поиск артефакта в общем пространстве имен
    aTmp = nt->globalFind("BOOLEAN");
    tc = dynamic_cast<TypeContext*>(aTmp->getContext());
    if(tc != nullptr) {
        VarContext* vContext = Creator::CreateVarContext(tc);
        module.addArtefact("boolVar01", vContext, true);
    }
    Context* boolContext01 = tc;

    // Создание действительной переменной
    // Поиск артефакта в общем пространстве имен
    aTmp = nt->globalFind("REAL");
    tc = dynamic_cast<TypeContext*>(aTmp->getContext());
    if(tc != nullptr) {
        VarContext* vContext = Creator::CreateVarContext(tc);
        module.addArtefact("realVar01", vContext, true);
    }

    // Создание символьной переменной
    // Поиск артефакта в общем пространстве имен
    aTmp = nt->globalFind("CHAR");
    tc = dynamic_cast<TypeContext*>(aTmp->getContext());
    if(tc != nullptr) {
        VarContext* vContext = Creator::CreateVarContext(tc);
        module.addArtefact("charVar01", vContext, true);
    }

    // Создание множественной переменной
    // Поиск артефакта в общем пространстве имен
    aTmp = nt->globalFind("SET");
    tc = dynamic_cast<TypeContext*>(aTmp->getContext());
    if(tc != nullptr) {
        VarContext* vContext = Creator::CreateVarContext(tc);
        module.addArtefact("setVar01", vContext, true);
    }

    // Операнды
    OperandVar opdBool01(boolContext01);


    // Создание списка команд для блока инициализации
    auto pInitInstructions = module.getInitInstructionBlock();
    InstructionLabel* pLabel00 = Creator::CreateInstructionLabel();
    pInitInstructions->addInstructionToTail(pLabel00);
    InstructionLabel* pLabel01 = Creator::CreateInstructionLabel();
    pInitInstructions->addInstructionToTail(pLabel01);
    InstructionLabel* pLabel02 = Creator::CreateInstructionLabel();
    pInitInstructions->addInstructionToTail(pLabel02);
    InstructionLabel iLabel02;
    InstructionLabel* pLabel03 = Creator::CreateInstructionLabel();
    pInitInstructions->addInstructionToTail(pLabel03);
    InstructionIfFalse ifFalse01(&opdBool01, pLabel02, nullptr);
    pInitInstructions->addInstructionToTail(&ifFalse01);
    InstructionLabel* pLabel04 = Creator::CreateInstructionLabel();
    pInitInstructions->addInstructionToTail(pLabel04);
    InstructionGoto* pGoto01 = Creator::CreateInstructionGoto(pLabel01);
    pInitInstructions->addInstructionToTail(pGoto01);
    InstructionIfTrue ifTrue01(&opdBool01, pLabel00, nullptr);
    pInitInstructions->addInstructionToTail(&ifTrue01);

    // Создание списка команд для блока финализации
    auto pFinalInstructions = module.getFinalInstructionBlock();
    pLabel00 = Creator::CreateInstructionLabel();
    pFinalInstructions->addInstructionToHead(pLabel00);
    pLabel01 = Creator::CreateInstructionLabel();
    pFinalInstructions->addInstructionToHead(pLabel01);
    pLabel02 = Creator::CreateInstructionLabel();
    pFinalInstructions->addInstructionToHead(pLabel02);
    pLabel03 = Creator::CreateInstructionLabel();
    pFinalInstructions->addInstructionToHead(pLabel03);
    pLabel04 = Creator::CreateInstructionLabel();
    pFinalInstructions->addInstructionToHead(pLabel04);
    pGoto01 = Creator::CreateInstructionGoto(pLabel01);
    pFinalInstructions->addInstructionToHead(pGoto01);

    module.debugOut();
}
