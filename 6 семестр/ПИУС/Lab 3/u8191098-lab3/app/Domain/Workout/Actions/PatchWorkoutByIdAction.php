<?php

namespace App\Domain\Workout\Actions;

use App\Models\Workout;

class PatchWorkoutByIdAction
{
    public function execute(int $workoutId, array $fields):Workout
    {
        $workout = Workout::findOrFail($workoutId);
        $workout->update($fields);

        return $workout;
    }
}
