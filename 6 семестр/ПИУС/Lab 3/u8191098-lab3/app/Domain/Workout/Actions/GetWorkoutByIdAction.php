<?php

namespace App\Domain\Workout\Actions;

use App\Models\Exercise;
use App\Models\Workout;

class GetWorkoutByIdAction
{
    public function execute(int $workoutId) :Workout
    {
        return Workout::findOrFail($workoutId);
    }
}
