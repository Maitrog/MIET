<?php

namespace App\Domain\Workout\Actions;

use App\Models\Workout;

class GetAllWorkoutAction
{
    public function execute() : array
    {
        return Workout::all()->toArray();
    }
}
