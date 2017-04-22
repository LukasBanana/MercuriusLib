/*
 * Service.h
 * 
 * This file is part of the "MercuriusLib" project (Copyright (c) 2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef MC_SERVICE_H
#define MC_SERVICE_H


#include <Merc/Export.h>
#include <thread>
#include <memory>
#include <atomic>


namespace Mc
{


//! Base class for all thread based services.
class MC_EXPORT Service
{

    public:

        Service(const Service&) = delete;
        Service& operator = (const Service&) = delete;

        virtual ~Service();

        // Returns true if this service is currently running.
        inline bool Running() const
        {
            return running_;
        }

    protected:

        Service() = default;

        //! Stops the running service.
        void Halt();

        template <class Function, class... Args>
        void Run(Function&& func, Args&&... args)
        {
            Halt();
            running_ = true;
            thread_ = std::thread(std::forward<Function>(func), std::forward<Args>(args)...);
        }

    private:

        std::thread         thread_;
        std::atomic_bool    running_ { false };

};


} // /namespace Mc


#endif



// ================================================================================
