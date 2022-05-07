<?php

namespace Database\Factories;

use App\Models\ExerciseType;
use App\Models\MuscleGroup;
use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Str;

class ExerciseFactory extends Factory
{
    public function definition()
    {
        return [
            'name'=> Str::random(10),
            'exercise_type_id'=> ExerciseType::
            inRandomOrder()->first()->id,
            'muscle_group_id'=> MuscleGroup::
            inRandomOrder()->first()->id,
        ];
    }
}
