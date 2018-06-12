//
// Created by yan on 5/18/18.
//


#include "algorithm_lib.h"
using namespace algorithm_lib;

#define SMALL_NUM 0.01
inline double sign_coulomb_friction(double in)
{
    if(in > SMALL_NUM)
    {
        return 1;
    }
    else if(in < -SMALL_NUM)
    {
        return -1;
    }
    else
    {
        return 0;
    }
//    return in/fabs(in);
}

inline double sigmoid_coulomb_friction(double in, double alpha)
{
    return 2.0/(1+exp(-alpha*in)) - 1.0;
}

inline double zero_coulomb_friction()
{
    return 0;
}


inline double zero_viscous_friction()
{
    return 0;
}


//#define SIGN(x) (sigmoid_coulomb_friction(x, 1))
//#define SIGN(x) (zero_coulomb_friction())
#define SIGN(x) (sign_coulomb_friction(x))
//#define VISCOUS_FRICTION(dq) (zero_viscous_friction())
#define VISCOUS_FRICTION(dq) (dq)

void ComputedTorqueController::computed_torque(double *param, double *q, double *dq, double *ddq, double *tau)
{
    double q1 = q[0], q2 = q[1], q3 = q[2];
    double dq1 = dq[0], dq2 = dq[1], dq3 = dq[2];
    double ddq1 = ddq[0], ddq2 = ddq[1], ddq3 = ddq[3];

    double t2 = sin(q2);
    double t3 = cos(q2);
    double t4 = cos(q3);
    double t5 = dq2*dq2;
    double t6 = sin(q3);
    double t7 = t3*t3;
    double t8 = t4*t4;
    double t9 = dq3*dq3;
    double t10 = dq1*dq1;
    double t11 = ddq3*3.247876606932213E-2;
    double t12 = t3*t4*1.451872361579693;
    double t13 = t4*t10*4.129178276052338E-2;
    double t14 = ddq1*t3*t6*3.650125814773187E-4;
    double t15 = ddq1*t2*t4*3.650125814773187E-4;
    double t16 = t7*t8*t10*8.663363510620643E-3;
    double t17 = ddq1*t2*t6*2.056331688877212E-3;
    double t18 = t2*t3*t8*t10*7.031844364963147E-2;
    double t19 = t4*t6*t7*t10*7.031844364963147E-2;

    tau[0] = ddq1*1.585132902999496E-1-dq1*3.295858309144478E-3-dq1*dq2*6.597140572921807E-3-dq1*dq3*4.331681755310322E-3-ddq2*t2*3.992525659509676E-3-ddq1*t4*1.689323090444424E-3+ddq2*t3*2.855838954244808E-3-ddq1*t6*8.258356552104676E-2-ddq1*t7*1.465470454850288E-1-ddq1*t8*3.515922182481574E-2-t2*t5*2.855838954244808E-3-t3*t5*3.992525659509676E-3-dq1*dq2*t4*8.258356552104676E-2-dq1*dq3*t4*8.258356552104676E-2+dq1*dq2*t6*1.689323090444424E-3+dq1*dq2*t7*1.319428114584361E-2+dq1*dq3*t6*1.689323090444424E-3+dq1*dq2*t8*8.663363510620643E-3+dq1*dq3*t7*8.663363510620643E-3+dq1*dq3*t8*8.663363510620643E-3+ddq1*t2*t3*6.597140572921807E-3+ddq2*t2*t4*3.650125814773187E-4-ddq2*t3*t4*2.056331688877212E-3+ddq3*t2*t4*3.650125814773187E-4+ddq2*t2*t6*2.056331688877212E-3-ddq3*t3*t4*2.056331688877212E-3+ddq1*t4*t6*4.331681755310322E-3+ddq2*t3*t6*3.650125814773187E-4+ddq3*t2*t6*2.056331688877212E-3+ddq1*t4*t7*1.689323090444424E-3+ddq3*t3*t6*3.650125814773187E-4+ddq1*t6*t7*8.258356552104676E-2+ddq1*t7*t8*7.031844364963147E-2+t2*t4*t5*2.056331688877212E-3+t3*t4*t5*3.650125814773187E-4-t2*t5*t6*3.650125814773187E-4+t3*t5*t6*2.056331688877212E-3+t2*t4*t9*2.056331688877212E-3+t3*t4*t9*3.650125814773187E-4-t2*t6*t9*3.650125814773187E-4+t3*t6*t9*2.056331688877212E-3+dq1*dq2*t2*t3*2.930940909700576E-1+dq1*dq3*t2*t3*7.031844364963147E-2+dq2*dq3*t2*t4*4.112663377754425E-3+dq2*dq3*t3*t4*7.300251629546374E-4+dq1*dq2*t4*t6*7.031844364963147E-2-dq2*dq3*t2*t6*7.300251629546374E-4+dq1*dq2*t4*t7*1.651671310420935E-1+dq1*dq3*t4*t6*7.031844364963147E-2+dq2*dq3*t3*t6*4.112663377754425E-3+dq1*dq3*t4*t7*8.258356552104676E-2-dq1*dq2*t6*t7*3.378646180888847E-3-dq1*dq3*t6*t7*1.689323090444424E-3-dq1*dq2*t7*t8*1.732672702124129E-2-dq1*dq3*t7*t8*1.732672702124129E-2+ddq1*t2*t3*t4*8.258356552104676E-2-ddq1*t2*t3*t6*1.689323090444424E-3-ddq1*t2*t3*t8*8.663363510620643E-3-ddq1*t4*t6*t7*8.663363510620643E-3-dq1*dq2*t2*t3*t4*3.378646180888847E-3-dq1*dq3*t2*t3*t4*1.689323090444424E-3-dq1*dq2*t2*t3*t6*1.651671310420935E-1-dq1*dq3*t2*t3*t6*8.258356552104676E-2-dq1*dq2*t2*t3*t8*1.406368872992629E-1-dq1*dq3*t2*t3*t8*1.406368872992629E-1-dq1*dq2*t4*t6*t7*1.406368872992629E-1-dq1*dq3*t4*t6*t7*1.406368872992629E-1-ddq1*t2*t3*t4*t6*7.031844364963147E-2+dq1*dq2*t2*t3*t4*t6*1.732672702124129E-2+dq1*dq3*t2*t3*t4*t6*1.732672702124129E-2;
    tau[1] = ddq2*1.528077694357909E-1-dq2*2.856777665428589E-3+t2*3.741982313198771+t3*3.293165531989504E-2+t10*3.298570286460903E-3+t11+t12+t13+t14+t15+t16+t17+t18+t19-ddq1*t2*3.992525659509676E-3+ddq1*t3*2.855838954244808E-3-ddq2*t4*1.689323090444424E-3-ddq3*t4*8.446615452222118E-4-ddq2*t6*8.258356552104676E-2-ddq3*t6*4.129178276052338E-2-t2*t4*2.969938981587777E-2-t2*t6*1.451872361579693-t3*t6*2.969938981587777E-2-t4*t9*4.129178276052338E-2+t6*t9*8.446615452222118E-4-t6*t10*8.446615452222118E-4-t7*t10*6.597140572921807E-3-t8*t10*4.331681755310322E-3-dq2*dq3*t4*8.258356552104676E-2+dq2*dq3*t6*1.689323090444424E-3-ddq1*t3*t4*2.056331688877212E-3-t2*t3*t10*1.465470454850288E-1-t4*t6*t10*3.515922182481574E-2-t4*t7*t10*8.258356552104676E-2+t6*t7*t10*1.689323090444424E-3+t2*t3*t4*t10*1.689323090444424E-3+t2*t3*t6*t10*8.258356552104676E-2-t2*t3*t4*t6*t10*8.663363510620643E-3;
    tau[2] = ddq2*3.247876606932213E-2+dq3*2.34783882395777E-3+t10*2.165840877655161E-3+t11+t12+t13+t14+t15+t16+t17+t18+t19-ddq2*t4*8.446615452222118E-4-ddq2*t6*4.129178276052338E-2-t2*t4*2.969938981587777E-2-t2*t6*1.451872361579693-t3*t6*2.969938981587777E-2+t4*t5*4.129178276052338E-2-t5*t6*8.446615452222118E-4-t6*t10*8.446615452222118E-4-t7*t10*4.331681755310322E-3-t8*t10*4.331681755310322E-3-ddq1*t3*t4*2.056331688877212E-3-t2*t3*t10*3.515922182481574E-2-t4*t6*t10*3.515922182481574E-2-t4*t7*t10*4.129178276052338E-2+t6*t7*t10*8.446615452222118E-4+t2*t3*t4*t10*8.446615452222118E-4+t2*t3*t6*t10*4.129178276052338E-2-t2*t3*t4*t6*t10*8.663363510620643E-3;

}

void ComputedTorqueController::gravity_term_torque(double *param, Eigen::Vector3d &q, Eigen::Vector3d &tau)
{
    double q1 = q(0), q2 = q(1), q3 = q(2);

    double t2 = cos(q2);
    double t3 = cos(q3);
    double t4 = sin(q2);
    double t5 = sin(q3);
    double t6 = t2*t3*3.004661361800823;

    tau[0] = 0;
    tau[1] = t2*(-1.901886904381854E-2)+t4*7.542770286293657+t6-t2*t5*6.455830978205876E-2-t3*t4*6.455830978205876E-2-t4*t5*3.004661361800823;
    tau[2] = t6-t2*t5*6.455830978205876E-2-t3*t4*6.455830978205876E-2-t4*t5*3.004661361800823;
}
void ComputedTorqueController::coriolis_term_torque(double *param, Eigen::Vector3d &v_q, Eigen::Vector3d &v_dq,
                                                    Eigen::Vector3d &v_tau)
{
    double q1 = v_q[0], q2 = v_q[1], q3 = v_q[2];
    double dq1 = v_dq[0], dq2 = v_dq[1], dq3 = v_dq[2];

    double t2 = dq2*dq2;
    double t3 = sin(q3);
    double t4 = cos(q2);
    double t5 = cos(q3);
    double t6 = t4*t4;
    double t7 = t5*t5;
    double t8 = sin(q2);
    double t9 = dq3*dq3;
    double t10 = dq1*dq1;
    double t11 = t5*t10*8.545367175763808E-2;
    double t12 = t6*t7*t10*4.271730593121489E-2;
    double t13 = t4*t7*t8*t10*1.68002954959188E-1;
    double t14 = t3*t5*t6*t10*1.68002954959188E-1;

    v_tau[0] = dq1*(-6.427788155523746E-3)-dq1*dq2*2.559475906521508E-2-dq1*dq3*2.135865296560744E-2-t2*t4*1.310487932007307E-2-t2*t8*5.769172065377966E-3+dq1*dq2*t3*3.672124042649214E-3+dq1*dq3*t3*3.672124042649214E-3-dq1*dq2*t5*1.709073435152762E-1+dq1*dq2*t6*5.118951813043015E-2-dq1*dq3*t5*1.709073435152762E-1+dq1*dq2*t7*4.271730593121489E-2+dq1*dq3*t6*4.271730593121489E-2+dq1*dq3*t7*4.271730593121489E-2+t2*t3*t4*1.206859118303365E-2+t2*t4*t5*3.440564451082133E-4-t2*t3*t8*3.440564451082133E-4+t2*t5*t8*1.206859118303365E-2+t3*t4*t9*1.206859118303365E-2+t4*t5*t9*3.440564451082133E-4-t3*t8*t9*3.440564451082133E-4+t5*t8*t9*1.206859118303365E-2+dq1*dq2*t3*t5*1.68002954959188E-1-dq1*dq2*t3*t6*7.344248085298428E-3+dq1*dq3*t3*t5*1.68002954959188E-1+dq2*dq3*t3*t4*2.41371823660673E-2-dq1*dq3*t3*t6*3.672124042649214E-3+dq1*dq2*t5*t6*3.418146870305523E-1+dq2*dq3*t4*t5*6.881128902164267E-4+dq1*dq2*t4*t8*5.454606559705737E-1+dq1*dq3*t5*t6*1.709073435152762E-1-dq1*dq2*t6*t7*8.543461186242977E-2+dq1*dq3*t4*t8*1.68002954959188E-1-dq2*dq3*t3*t8*6.881128902164267E-4-dq1*dq3*t6*t7*8.543461186242977E-2+dq2*dq3*t5*t8*2.41371823660673E-2-dq1*dq2*t3*t5*t6*3.36005909918376E-1-dq1*dq2*t3*t4*t8*3.418146870305523E-1-dq1*dq3*t3*t5*t6*3.36005909918376E-1-dq1*dq3*t3*t4*t8*1.709073435152762E-1-dq1*dq2*t4*t5*t8*7.344248085298428E-3-dq1*dq3*t4*t5*t8*3.672124042649214E-3-dq1*dq2*t4*t7*t8*3.36005909918376E-1-dq1*dq3*t4*t7*t8*3.36005909918376E-1+dq1*dq2*t3*t4*t5*t8*8.543461186242977E-2+dq1*dq3*t3*t4*t5*t8*8.543461186242977E-2;
    v_tau[1] = dq2*(-9.416793131504031E-3)+t10*1.279737953260754E-2+t11+t12+t13+t14+t3*t9*1.836062021324607E-3-t3*t10*1.836062021324607E-3-t5*t9*8.545367175763808E-2-t6*t10*2.559475906521508E-2-t7*t10*2.135865296560744E-2+dq2*dq3*t3*3.672124042649214E-3-dq2*dq3*t5*1.709073435152762E-1-t3*t5*t10*8.4001477479594E-2+t3*t6*t10*3.672124042649214E-3-t5*t6*t10*1.709073435152762E-1-t4*t8*t10*2.727303279852868E-1+t3*t4*t8*t10*1.709073435152762E-1+t4*t5*t8*t10*3.672124042649214E-3-t3*t4*t5*t8*t10*4.271730593121489E-2;
    v_tau[2] = dq3*1.519476848703428E-3+t10*1.067932648280372E-2+t11+t12+t13+t14-t2*t3*1.836062021324607E-3+t2*t5*8.545367175763808E-2-t3*t10*1.836062021324607E-3-t6*t10*2.135865296560744E-2-t7*t10*2.135865296560744E-2-t3*t5*t10*8.4001477479594E-2+t3*t6*t10*1.836062021324607E-3-t5*t6*t10*8.545367175763808E-2-t4*t8*t10*8.4001477479594E-2+t3*t4*t8*t10*8.545367175763808E-2+t4*t5*t8*t10*1.836062021324607E-3-t3*t4*t5*t8*t10*4.271730593121489E-2;

}

void ComputedTorqueController::friction_torque(double *param, Eigen::Vector3d &v_dq, Eigen::Vector3d &v_tau)
{

}

void ComputedTorqueController::inertia_matrix(double *param, Eigen::Vector3d &q, Eigen::Matrix3d &M)
{
    double q1 = q[0], q2 = q[1], q3 = q[2];

    double t2 = cos(q3);
    double t3 = sin(q3);
    double t4 = cos(q2);
    double t5 = t4*t4;
    double t6 = t2*t2;
    double t7 = sin(q2);
    double t8 = t3*t4*3.440564451082133E-4;
    double t9 = t2*t7*3.440564451082133E-4;
    double t10 = t3*t7*1.206859118303365E-2;
    double t11 = t4*5.769172065377966E-3;
    double t13 = t2*t4*1.206859118303365E-2;
    double t12 = t7*(-1.310487932007307E-2)+t8+t9+t10+t11-t13;
    double t14 = t2*(-1.836062021324607E-3)-t3*8.545367175763808E-2+7.510809364927562E-2;

    M(0,0) = t2*(-3.672124042649214E-3)-t3*1.709073435152762E-1-t5*2.727303279852868E-1-t6*8.4001477479594E-2+t2*t3*2.135865296560744E-2+t2*t5*3.672124042649214E-3+t3*t5*1.709073435152762E-1+t4*t7*2.559475906521508E-2+t5*t6*1.68002954959188E-1-t2*t3*t5*4.271730593121489E-2+t2*t4*t7*1.709073435152762E-1-t3*t4*t7*3.672124042649214E-3-t4*t6*t7*4.271730593121489E-2-t2*t3*t4*t7*1.68002954959188E-1+2.874956113256997E-1;
    M(0,1) = t12;
    M(0,2) = t8+t9+t10-t2*t4*1.206859118303365E-2;
    M(1,0) = t12;
    M(1,1) = t2*(-3.672124042649214E-3)-t3*1.709073435152762E-1+3.060000154266335E-1;
    M(1,2) = t14;
    M(2,0) = t8+t9+t10-t13;
    M(2,1) = t14;
    M(2,2) = 7.510809364927562E-2;
}

void ComputedTorqueController::do_computed_torque_control(Eigen::Vector3d &v_q, Eigen::Vector3d &v_dq,
                                                          Eigen::Vector3d &v_qd, Eigen::Vector3d &v_dqd,
                                                          Eigen::Vector3d &v_ddqd, Eigen::Vector3d &v_tau)
{
    Eigen::Vector3d v_a;
    Eigen::Vector3d v_e;
    Eigen::Vector3d v_de;
    Eigen::Vector3d v_g;
    Eigen::Vector3d v_c;

    gravity_term_torque(param, v_q, v_g);
    coriolis_term_torque(param, v_q, v_dq, v_c);

    Eigen::Matrix3d M;
    inertia_matrix(param, v_q, M);

    v_e = v_qd - v_q;
    v_de = v_dqd - v_dq;
    v_a = kp*v_e + kd*v_de + v_ddqd;

    v_tau = v_g + M*v_a + v_c;


//    for(int i = 0; i < DOF; i++)
//    {
//        e[i] = qd[i] - q[i];
//        de[i] = dqd[i] - dq[i];
//
//        a[i] = kp[i]*e[i] + kd[i]*de[i] + ddqd[i];
//
//        tau[i] = a[i] + gravity_compensation[i];
//
//    }
////    cout << "kp: " << kp[0] << ", " << kp[1] << ", " << kp[2] << endl;
////    cout << "kd: " << kd[0] << ", " << kd[1] << ", " << kd[2] << endl;
////    cout << "e: " << e[0] << ", " << e[1] << ", " << e[2] << " de: " << de[0] << ", " << de[1] << ", " << de[2] << endl;
////    cout << "a: " << a[0] << ", " << a[1] << ", " << a[2] << endl;
////    computed_torque(param, q, dq, a, tau);
    static int cnt = 0;
    cnt++;
    if(cnt%500 == 0)
    {
        cout << "inertia matrix: " << endl << M << endl;
        cout << "gravity torque: " << endl << v_g << endl;
    }

}

void trajectory_generation(double start, double end, double T, double dt, vector<double> *q, vector<double > *dq, vector<double> *a)
{
    int N = T/dt+1;
    double a2 = 2/(T*T), a3 = 0.5, a4 = 2/T, a5 = -2/(T*T);
    double t = 0, t2, t3, t4, t5;

    q->resize(N);
    dq->resize(N);
    a->resize(N);
    for(int i = 0; i < N; i++)
    {
        t = i*dt;
        t2 = t*t;
        t3 = t2*t;
        t4 = t3*t;
        t5 = t4*t;

        (*q)[i] = a2*t2 + a3*t3 + a4*t4 + a5*t5;
        (*dq)[i] = 2*a2*t + 3*a3*t2 + 4*a4*t3 + 5*a5*t4;
        (*a)[i] = 2*a2 + 6*a3*t + 12*a4*t2 + 20*a5*t3;
    }
}


double Filter::do_filter(double x)
{
    auto state_len = z.size();
    if(!initilized)
    {
        init_z(x);
        initilized = true;
    }
    double y = b[0]*x + z[0];
    for(int i = 0; i < state_len-1; i++)
    {
        z[i] = b[i+1]*x + z[i+1] - a[i+1]*y;
    }
    z[state_len-1] = b[state_len]*x - a[state_len]*y;

    return y;
}
