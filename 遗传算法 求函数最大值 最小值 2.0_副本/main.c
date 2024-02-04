#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define POPULATION_SIZE 100000 //初始样本数
#define MAX_GENERATIONS 10000 //最大代数
#define MUTATION_RATE 0.01 //变异概率
#define CROSSOVER_RATE 0.8 //交叉概率

typedef struct {
    int x;
    double fitness;
} Individual;

// 定义函数
double function(int x) {
    // 在这里输入函数 这里的x使用弧度制
    return pow(x, 2 * cos(3 * x)) + 3 * sin(5 * x) / pow(pow(3 * sin(x), 2), log(3 * x)) / pow(cos(log(5 * x)), x);
}

// 适应度函数
double fitness(double y) {
    // 在这里输入适应度函数 求最大值时适应度函数就是原函数
    return y;
}

// 初始化种群
void initialize_population(Individual *population) {
    for(int i = 0; i < POPULATION_SIZE; i++) {
        population[i].x = rand() % 20001 - 10000; // x的范围是-10000到10000
        population[i].fitness = fitness(function(population[i].x));
    }
}

// 选择 采用轮盘赌方式
Individual selection(Individual *population) {
    int i = rand() % POPULATION_SIZE;
    int j = rand() % POPULATION_SIZE;
    if(population[i].fitness > population[j].fitness)
        return population[i];
    else
        return population[j];
}

// 交叉
void crossover(Individual *parent1, Individual *parent2) {
    if((double)rand() / RAND_MAX < CROSSOVER_RATE) {
        int temp = parent1->x;
        parent1->x = parent2->x;
        parent2->x = temp;
    }
}

// 变异
void mutation(Individual *individual) {
    if((double)rand() / RAND_MAX < MUTATION_RATE)
        individual->x = rand() % 20001 - 10000; // x的范围是-10000到10000
}

// 遗传算法主函数
int main() {
    Individual population[POPULATION_SIZE];
    Individual new_population[POPULATION_SIZE];

    initialize_population(population);

    Individual best_individual = population[0];
    Individual worst_individual = population[0];

    for(int generation = 0; generation < MAX_GENERATIONS; generation++) {
        for(int i = 0; i < POPULATION_SIZE; i++) {
            Individual parent1 = selection(population);
            Individual parent2 = selection(population);
            crossover(&parent1, &parent2);
            mutation(&parent1);
            mutation(&parent2);
            parent1.fitness = fitness(function(parent1.x));
            parent2.fitness = fitness(function(parent2.x));
            new_population[i] = parent1;
            if(++i < POPULATION_SIZE)
                new_population[i] = parent2;
        }

        for(int i = 0; i < POPULATION_SIZE; i++) {
            population[i] = new_population[i];
            if(population[i].fitness > best_individual.fitness)
                best_individual = population[i];
            if(population[i].fitness < worst_individual.fitness)
                worst_individual = population[i];
        }
    }

    printf("最大值: x = %d, y = %f\n", best_individual.x, function(best_individual.x));
    printf("最小值: x = %d, y = %f\n", worst_individual.x, function(worst_individual.x));

    return 0;
}
