<?php

namespace App\Domain\Workout\Actions;

use App\Models\Workout;

class CreateWorkoutAction
{
    public function execute(array $fields): Workout
    {
        return Workout::create($fields);
    }
}
