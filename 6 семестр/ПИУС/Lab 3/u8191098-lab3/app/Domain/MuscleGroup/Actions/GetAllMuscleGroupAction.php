<?php

namespace App\Domain\MuscleGroup\Actions;

use App\Models\MuscleGroup;

class GetAllMuscleGroupAction
{
    public function execute() : array
    {
        return MuscleGroup::all()->toArray();
    }
}
