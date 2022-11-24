#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>

#include "ODESolver.h"

void run_rk(const Context &context);
void run_ae(const Context &context);
void run_ai(const Context &context);

int main()
{
    // Creating function, Context with function and creating ODESolver with Context
    std::function<std::vector<double>(double t, std::vector<double> x)> f =
            [](double t, std::vector<double> x) -> std::vector<double>{
        std::vector<double> res(x.size());

        res[0]=10.0*(x[1]-x[0]);
        res[1]=x[0]*(28.0-x[2])-x[1];
        res[2]=x[0]*x[1]-8.0*x[2]/3.0;

        return res;
    };

    Context context = Context(f);
    context.x_0 = {10, 10, 10};
    context.n = 10;
    context.h = 5e-5;
    context.t_end = 25;

    // Run calculation
    std::thread rk(run_rk, context);
    std::thread ae(run_ae, context);
    std::thread ai(run_ai, context);

    rk.join();
    ae.join();
    ai.join();

    return 0;
}

void run_rk(const Context &context){
    ODESolver odeSolver = ODESolver(context);

    odeSolver.rk();

    std::ofstream rk("rk.dat");

    for (auto &step: odeSolver.Result)
    {
        auto [ t, x ] = step;

        rk << std::fixed << std::setprecision(10) << t << " ";

        for (auto &item: x)
        {
            rk << item << " ";
        }

        rk << std::endl;
    }

    rk.close();
}

void run_ae(const Context &context){
    ODESolver odeSolver = ODESolver(context);

    odeSolver.ae();

    std::ofstream ae("ae.dat");

    for (auto &step: odeSolver.Result)
    {
        auto [ t, x ] = step;

        ae << std::fixed << std::setprecision(10) << t << " ";

        for (auto &item: x)
        {
            ae << item << " ";
        }

        ae << std::endl;
    }

    ae.close();
}

void run_ai(const Context &context){
    ODESolver odeSolver = ODESolver(context);

    odeSolver.ai();

    std::ofstream ai("ai.dat");

    for (auto &step: odeSolver.Result)
    {
        auto [ t, x ] = step;

        ai << std::fixed << std::setprecision(10) << t << " ";

        for (auto &item: x)
        {
            ai << item << " ";
        }

        ai << std::endl;
    }

    ai.close();
}
