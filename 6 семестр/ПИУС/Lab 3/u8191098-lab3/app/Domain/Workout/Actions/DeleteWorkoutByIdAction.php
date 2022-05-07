<?php

namespace App\Domain\Workout\Actions;

use App\Models\Workout;

class DeleteWorkoutByIdAction
{
    public function execute(int $workoutId)
    {
        $workout = Workout::findOrFail($workoutId);
        $workout->delete();

        return $workout;
    }
}
