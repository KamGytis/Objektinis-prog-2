#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <sstream>
#include "studentas.h"

// rules of five testai

TEST(RuleOfFiveTest, DefaultConstructor) {
    Studentas s;
    EXPECT_EQ(s.getVardas(), "");
    EXPECT_EQ(s.getPavarde(), "");
    EXPECT_EQ(s.getEgz(), 0);
    EXPECT_DOUBLE_EQ(s.getRez(), 0.0);
    EXPECT_EQ(s.getPazSkaicius(), 0);
}

TEST(RuleOfFiveTest, ParameterizedConstructor) {
    std::vector<int> paz = { 8, 9, 7 };
    Studentas s("Jonas", "Jonaitis", paz, 10);
    EXPECT_EQ(s.getVardas(), "Jonas");
    EXPECT_EQ(s.getPavarde(), "Jonaitis");
    EXPECT_EQ(s.getEgz(), 10);
    EXPECT_EQ(s.getPazSkaicius(), 3);
    EXPECT_EQ(s.getPaz()[0], 8);
}

TEST(RuleOfFiveTest, CopyConstructor) {
    std::vector<int> paz = { 8, 9, 7 };
    Studentas original("Jonas", "Jonaitis", paz, 10);
    original.skaiciuotiRez(1);

    Studentas kopija(original);
    EXPECT_EQ(kopija.getVardas(), original.getVardas());
    EXPECT_EQ(kopija.getPaz(), original.getPaz());
    EXPECT_DOUBLE_EQ(kopija.getRez(), original.getRez());

    // Gilioji kopija – pakeitus kopija originalas lieka nepakites
    kopija.setVardas("Petras");
    EXPECT_EQ(original.getVardas(), "Jonas");
}

TEST(RuleOfFiveTest, MoveConstructor) {
    std::vector<int> paz = { 5, 6 };
    Studentas original("Ona", "Onaite", paz, 7);
    Studentas perkeltas(std::move(original));

    EXPECT_EQ(perkeltas.getVardas(), "Ona");
    EXPECT_EQ(perkeltas.getPazSkaicius(), 2);
    EXPECT_EQ(original.getVardas(), "");      // originalas paliktas tuscias
    EXPECT_EQ(original.getPazSkaicius(), 0);
}

TEST(RuleOfFiveTest, CopyAssignment) {
    Studentas a("Jonas", "Jonaitis", { 8, 9 }, 10);
    Studentas b;
    b = a;
    EXPECT_EQ(b.getVardas(), "Jonas");
    EXPECT_EQ(b.getPaz(), a.getPaz());

    // Saves priskyrimas
    a = a;
    EXPECT_EQ(a.getVardas(), "Jonas");
}

TEST(RuleOfFiveTest, MoveAssignment) {
    Studentas a("Ona", "Onaite", { 5, 6 }, 7);
    Studentas b;
    b = std::move(a);
    EXPECT_EQ(b.getVardas(), "Ona");
    EXPECT_EQ(a.getVardas(), "");
}

// papildomi testai

TEST(CalculationTest, Vidurkis) {
    Studentas s("Test", "Test", { 6, 8, 10 }, 0);
    EXPECT_DOUBLE_EQ(s.vidurkis(), 8.0);
}

TEST(CalculationTest, Mediana) {
    Studentas s("Test", "Test", { 3, 9, 5 }, 0);
    EXPECT_DOUBLE_EQ(s.mediana(), 5.0);
}

TEST(CalculationTest, GalutinisRezultatas) {
    Studentas s("Test", "Test", { 8, 10, 6 }, 8);
    s.skaiciuotiRez(1);
    EXPECT_DOUBLE_EQ(s.getRez(), 8.0);
}

TEST(IOTest, InputOperator) {
    Studentas s;
    std::istringstream iss("Jonas Jonaitis 8 9 7 10");
    iss >> s;
    EXPECT_EQ(s.getVardas(), "Jonas");
    EXPECT_EQ(s.getPazSkaicius(), 3);
}

TEST(ClassificationTest, Islaike) {
    Studentas s;
    s.setRez(5.0);
    EXPECT_TRUE(s.islaike());
    s.setRez(4.9);
    EXPECT_FALSE(s.islaike());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "\n========== STUDENTU SISTEMOS UNIT TESTAI (Google Test) ==========\n\n";
    return RUN_ALL_TESTS();
}