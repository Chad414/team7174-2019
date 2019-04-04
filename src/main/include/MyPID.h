#pragma once

namespace protobot{
    class ProtoPID{
        public:
        ProtoPID(float kp, float ki, float kd, float filtTime, float dt)
            :kp_(kp),
            ki_(ki),
            kd_(kd),
            intErr_(0),
            prevIntErr_(0),
            prevFiltMeas_(0),
            currFiltMeas_(0),
            filtTime_(filtTime),
            dt_(dt),
            pControl_(0),
            iControl_(0),
            dControl_(0),
            error_(0),
            command_(0)
        {}
        double compute(double currMeas, double setpoint){
            error_ = setpoint - currMeas;
            intErr_ = prevIntErr_ + error_ * dt_;
            double alpha = dt_/(filtTime_ + dt_);
            currFiltMeas_ = (1-alpha) * prevFiltMeas_ + alpha * currMeas;
            pControl_ = kp_ * error_;
            iControl_ = ki_ * intErr_;
            dControl_ = (-kd_ * currFiltMeas_) / dt_;
            
            command_ = pControl_ + iControl_ + dControl_;

            if (command_ >1.0){
                command_ = 1.0;
                intErr_ = intErr_ - error_ * dt_;
            }

            else if (command_ <-1.0){
                command_ = -1.0;
                intErr_ = intErr_ - error_ * dt_;
            }

            return command_;
        }

        double getCommand(){
            return command_;
        }
        
        double getFiltMeas(){
            return currFiltMeas_;
        }

        double getError(){
            return error_;
        }

        double reset(){
            intErr_ = 0;
            prevIntErr_ = 0;
            prevFiltMeas_ = 0;
            currFiltMeas_ = 0;
            error_ = 0;
        }

        double setGains(){

        }

        private:
        double kp_;
        double ki_;
        double kd_;
        double intErr_;
        double prevIntErr_;
        double prevFiltMeas_;
        double currFiltMeas_;
        double filtTime_;
        double dt_;
        double pControl_;
        double iControl_;
        double dControl_;
        double command_;
        double error_;


    };
};