#include <gtest/gtest.h>
#include "studentas.h"
#include "zmogus.h"
#include <vector>

// 1. Rule of Five testai 

TEST(RuleOfFive, DefaultConstructor) {
    Studentas s;
    EXPECT_EQ(s.getVardas(), "");
    EXPECT_EQ(s.getPavarde(), "");
    EXPECT_EQ(s.getEgz(), 0);
    EXPECT_DOUBLE_EQ(s.getRez(), 0.0);
    EXPECT_EQ(s.getPazSkaicius(), 0u);
}

TEST(RuleOfFive, ParameterConstructor) {
    Studentas s("Jonas", "Jonaitis", { 8,9,7 }, 10);
    EXPECT_EQ(s.getVardas(), "Jonas");
    EXPECT_EQ(s.getPavarde(), "Jonaitis");
    EXPECT_EQ(s.getEgz(), 10);
    EXPECT_EQ(s.getPazSkaicius(), 3u);
    EXPECT_EQ(s.getPaz()[0], 8);
}

TEST(RuleOfFive, CopyConstructor) {
    Studentas a("Petras", "Petraitis", { 5,6 }, 7);
    Studentas b(a);
    EXPECT_EQ(b.getVardas(), "Petras");
    EXPECT_EQ(b.getPavarde(), "Petraitis");
    b.setVardas("Antanas");
    EXPECT_EQ(a.getVardas(), "Petras");   // gili kopija
}

TEST(RuleOfFive, MoveConstructor) {
    Studentas a("Ona", "Onaite", { 9,10 }, 8);
    Studentas b(std::move(a));
    EXPECT_EQ(b.getVardas(), "Ona");
    EXPECT_EQ(a.getVardas(), "");         // originalas tuscias
    EXPECT_EQ(a.getPazSkaicius(), 0u);
}

TEST(RuleOfFive, CopyAssignment) {
    Studentas a("Kazys", "Kazlauskas", { 7,8 }, 9);
    Studentas b;
    b = a;
    EXPECT_EQ(b.getVardas(), "Kazys");
    a.setVardas("Laimis");
    EXPECT_EQ(b.getVardas(), "Kazys");
}

TEST(RuleOfFive, MoveAssignment) {
    Studentas a("Rita", "Ritaite", { 6,7 }, 8);
    Studentas b;
    b = std::move(a);
    EXPECT_EQ(b.getVardas(), "Rita");
    EXPECT_EQ(a.getVardas(), "");
}

TEST(RuleOfFive, SelfAssignment) {
    Studentas a("A", "A", { 1 }, 2);
    a = a;
    EXPECT_EQ(a.getVardas(), "A");
}

// 2. Kiti funkciniai testai

TEST(Functional, AverageAndMedian) {
    Studentas s("T", "T", { 4,6,8,10 }, 0);
    EXPECT_DOUBLE_EQ(s.vidurkis(), 7.0);
    EXPECT_DOUBLE_EQ(s.mediana(), 7.0);   // (6+8)/2 = 7
}

TEST(Functional, CalculateResultMean) {
    Studentas s("X", "X", { 8,10,6 }, 8); // vidurkis = 8
    s.skaiciuotiRez(1);
    // 8*0.4 + 8*0.6 = 8.0
    EXPECT_DOUBLE_EQ(s.getRez(), 8.0);
}

TEST(Functional, CalculateResultMedian) {
    Studentas s("Y", "Y", { 4,6,8 }, 10); // mediana = 6
    s.skaiciuotiRez(2);
    // 6*0.4 + 10*0.6 = 2.4+6 = 8.4
    EXPECT_DOUBLE_EQ(s.getRez(), 8.4);
}

TEST(Functional, IsPassed) {
    Studentas s;
    s.setRez(4.9);
    EXPECT_FALSE(s.islaike());
    s.setRez(5.0);
    EXPECT_TRUE(s.islaike());
}

// 3. Abstraktumo ir polimorfizmo testai

TEST(AbstractZmogus, Polymorphism) {
    Zmogus* ptr = new Studentas("Polimorfas", "Test", { 1,2 }, 3);
    EXPECT_EQ(ptr->getVardas(), "Polimorfas");
    delete ptr;   // virtualus destruktorius
}

TEST(AbstractZmogus, OutputOperatorUsesVirtualPrint) {
    Studentas s("Vardas", "Pavarde", { 5,5 }, 5);
    s.skaiciuotiRez(1);
    std::ostringstream oss;
    oss << s;
    std::string out = oss.str();
    EXPECT_NE(out.find("Vardas"), std::string::npos);
    EXPECT_NE(out.find("Rez"), std::string::npos);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}